#include "ArtillertyCalculator.h"

int comparePositions(const void* p, const void* q)
{
    Position* a = *(Position**)p;
    Position* b = *(Position**)q;
    if (a->angle > b->angle)
        return 1;
    else
        return -1;
}

double getDistance(const Point* a, const Point* b) {
	return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}

int calculateDistances(const Point* points, double** distances, size_t pointsNumber) {
	for (size_t i = 0; i < pointsNumber; i++)
		for (size_t j = 0; j < i + 1; j++) {
            distances[i][j] = i == j ? 0 : getDistance(&points[i], &points[j]);
            if (isnan(distances[i][j])) {
                handleError(CALCULATING_ERROR);
                return 0;
            }
		}
	return 1;
}

int getPointsInside(size_t pointIndex, int radius, size_t size, const double** distances, const Point* points, Position* bestPosition) {

    const double PI = acos(-1.0);

    // Вращаем окружность вокруг точки и рассчитываем углы, при которых другие точки входят в окружность и выходят из нее.

    Vector positions;
    if (!vectorInit(&positions, sizeof(Position))) {
        handleError(-1);
        return -1;
    }

    for (size_t j = 0; j < size; j++) {
        size_t fi, si;
        if (j > pointIndex) {
            fi = j; si = pointIndex;
        } else{
            si = j; fi = pointIndex;
        }
        if (pointIndex != j && distances[fi][si] <= 2 * radius)
        {
            double dy = points[j].y - points[pointIndex].y;
            double dx = points[j].x - points[pointIndex].x;
            double ijAngle = acos(distances[fi][si] / (2 * radius));
            double xjAngle = atan2(dy, dx);

            double entryAngle = xjAngle - ijAngle;
            while (entryAngle < 0)      entryAngle += 2 * PI;
            while (entryAngle > 2 * PI) entryAngle -= 2 * PI;

            double exitAngle = xjAngle + ijAngle;
            while (exitAngle < 0)       exitAngle += 2 * PI;
            while (exitAngle > 2 * PI)  exitAngle -= 2 * PI;

            if (!vectorPush(&positions,    &(Position) { entryAngle, 1 })
                || !vectorPush(&positions, &(Position) { exitAngle, 0 })) {
                handleError(-1);
                return -1;
            }
        }
    }

    vectorSort(&positions, comparePositions);

    int pointsInsideCurrent = 1, pointsInsideMax = 1;
    Position maxPosition = {0.0, 0};
    
    for (size_t i = 0; i < vectorGetSize(&positions); i++)
    {
        Position* position = vectorGetElement(&positions, i);
        if (position->entered)
            pointsInsideCurrent++;
        else
            pointsInsideCurrent--;
        if (pointsInsideCurrent > pointsInsideMax) {
            maxPosition = *position;
            pointsInsideMax = pointsInsideCurrent;
        }
    }

    vectorClear(&positions);
    *bestPosition = maxPosition;
    return pointsInsideMax;
}

double** initDistances(const Point* points, size_t size) {

    /*
        Объявляем матрицу расстояний, отсекая элементы ниже главной диагонали
        В случае нехватки памяти можно отечь и саму главную диагональ, но все элементы в матрице будут сдвинуты,
        т.е. матрица вида

              a b c ...

          a   0
          b   # 0 
          c   # # 0
         ...  # # # ...

        переходит в

             b c ...

          a  
          b  #
          c  # #
         ... 

         Чтобы получить расстояние от точки a до точки b нужно будет обратитья не к distances[1][0], а к distances[0][0], что не так удобно для восприятия
    */

    // (1.0 + (double)size) / 2 * size - сумма чисел от 1 до size - из формулы суммы первых n членов арифметической прогрессии
    size_t elementsNumber = (size_t)((1.0 + (double)size) / 2 * size);
    double** distances = (double**)malloc(size * sizeof(double*) + elementsNumber * sizeof(double));
 
    if (!distances) {
        handleError(MEMORY_ERROR);
        return NULL;
    }
    
    //Стандарт гарантирует, что sizeof(char) всегда равен 1
    char* arrayStart = (char*)distances;
    arrayStart += size * sizeof(double*);

    for (size_t i = 0; i < size; i++) {
        size_t en = (size_t)((1.0 + (double)i) / 2 * i);
        distances[i] = (double*)(arrayStart + en * sizeof(double));
    }

	calculateDistances(points, distances, size);

    return distances;
}

Point getCircleCenter(const Position* position, const Point* point, int radius) {
    Point circleCenter = { -1.0, -1.0 };
    circleCenter.x = radius * cos(position->angle) + point->x;
    circleCenter.y = radius * sin(position->angle) + point->y;
    return circleCenter;
}

size_t calculateTarget(const Point* points, Point* optimalPoint, size_t size, int radius) {
    double** distances = initDistances(points, size);
    if (!distances)
        handleError(-1);
	
    int maxTargetsHit = 0, pointIndex = -1;

    Position maxPos;
    for (int i = 0; i < size; i++) {
        Position bestPosition;
        int x = getPointsInside(i, radius, size, distances, points, &bestPosition);
        if (x > maxTargetsHit) {
            pointIndex    = i;
            maxPos        = bestPosition;
            maxTargetsHit = x;
        }
    }

    Point bestPoint = getCircleCenter(&maxPos, &points[pointIndex], radius);
    *optimalPoint = bestPoint;

    free(distances);
	return maxTargetsHit;
}