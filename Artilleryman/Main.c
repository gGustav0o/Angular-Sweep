/**
	\file
	\brief ќсновной файл программы

	—читывает аргументы и данные из файла, выводит результаты вычислений.
**/

#include "ArtillertyCalculator.h"
#include "Errors.h"

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#pragma warning(disable:4996)

#define MIN_COORDINATE  0
#define MAX_COORDINATE  99
#define ARRAY_BASE_SIZE 16

/**
	—читывает данные из файла в массив
	\param[in] fileName им€ файла
	\param[out] points указатель на массив, в который будет производитьс€ запись
	\return количетво считанных элементов
**/
int readPoints(const char *fileName, Point** points) {
	FILE* file;
	if ((file = fopen(fileName, "r")) != NULL) {

		*points = (Point*)malloc(sizeof(Point) * ARRAY_BASE_SIZE);
		size_t currentSize = ARRAY_BASE_SIZE;
		if (!points || !*points) {
			if (fclose(file) == EOF)
				handleError(FILE_CLOSING_ERROR);
			handleError(MEMORY_ERROR);
			return -1;
		}


		int x = -1, y = -1;
		size_t actualSize = 0;
		int n;

        while ((n = fscanf(file, "%d, %d\n", &x, &y)) != EOF)
        {
			if (n != 2 
				|| x < MIN_COORDINATE || x > MAX_COORDINATE
				|| y < MIN_COORDINATE || y > MAX_COORDINATE)
				handleError(FILE_READING_ERROR);

			if (actualSize >= currentSize) {
				Point *temp = realloc(*points, (size_t)(currentSize * 1.5));
				if (temp) {
					*points = temp;
					currentSize = (size_t)(currentSize * 1.5);
				}
				else
					handleError(MEMORY_ERROR);
			}

			(*points)[actualSize].x = x;
			(*points)[actualSize].y = y;
			actualSize++;
        }

		if (fclose(file) == EOF)
			handleError(FILE_CLOSING_ERROR);
		return (int)actualSize;
	}
	else 
		handleError(FILE_OPENING_ERROR);

	return -1;
}

int main(int argc, char** argv) {
	if (argc != 3)
		handleError(UNEXPECTED_NUMBER_OF_ARGUMENTS);

	char* fileName = argv[1];
	int   range    = (int)strtol(argv[2], NULL, 10);

	Point* points = NULL;
	int size   = readPoints(fileName, &points);
	if (!points) {
		handleError(-1);
		return -1;
	}

	Point  optimalPoint = {-1, -1};
	size_t pointsNumber = calculateTarget(points, &optimalPoint, size, range);

	free(points);
	
	if (pointsNumber < 0)
		handleError(CALCULATING_ERROR);
	
	printf("Number of targets hit: %zd\nOptimal point coordinates: (%f, %f)"
		, pointsNumber, optimalPoint.x, optimalPoint.y);

	
	return 0;
}