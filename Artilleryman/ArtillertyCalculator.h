/**
	\file
	\brief Заголовочный файл модуля, в котором производятся рассчеты.

	Angular Sweep\n
	Time Complexity: O(n*n*lon(n))\n\n

	В этом файле перечислены функции и структуры, используемые для рассчета.\n
	Модуль реализует алгоритм угловой развертки. 
**/

#ifndef ARTILLERY_CALCULATOR_H
#define ARTILLERY_CALCULATOR_H

#include <stdio.h>
#include <math.h>
#include "Errors.h"
#include "Vector.h"

/** @struct Point
	Точка в двумерном евклидовом пространтве
	@var Point::x
		x-координата
	@var Point::y
		y-координата
 **/
typedef struct {
	double x, y;
} Point;

/** @struct Position
	Описывает положение точки.\n
	Радиус окружности и точка, относительно которой мы задаем положение, известны, значит положение точки однозначно задается углом относительно оси X. 
	@var Position::angle
		Угол относительно оси X
	@var Position::entered
		Флаг, показывающий, вошла точка в окружность или вышла из нее
 **/
typedef struct {
	double    angle;
	short     entered;
} Position;

/**
	Функция сравнения позиций точек для сортировки
	\param p, q указатели на позиции
	\return 1, если угол позиции p меньше угла позиции q, в ином лучае - -1
**/
int comparePositions(const void* p, const void* q);

/**
	Рассчитать евклидово расстояние между точками
	\param a, b указатели на точки
	\return расстояние между точками в двумерном евклидовом пространстве
**/
double getDistance(const Point* a, const Point* b);

/**
	Рассчитать расстояния между всеми данными точками
	\param[in] points массив точек
	\param[out] distances указатель на матрицу расстояний
	\param[in] pointsNumber количество точек
	\return 1, если рассчет прошел без ошибок, в противном случае - 0
**/
int calculateDistances(const Point* points, double** distances, size_t pointsNumber);

/**
	Алгоритм угловой развертки. Рассчитать наилучшее положение окружности, содержащей заданную точку.
	\param[in] pointIndex индекс точки в масиве
	\param[in] radius радиус окружности
	\param[in] size количество точек
	\param[in] distances матрица расстояний между точками
	\param[in] points массив точек
	\param[out] наилучшая позиция центра окружности относительно заданной точки
	\return количество точек, попавших в окружность, в наилучшей позиции
**/
int getPointsInside(size_t pointIndex, int radius, size_t size, const double** distances, const Point* points, Position* bestPosition);

/**
	Создать матрицу расстояний между точками\n
	Создается верхнетреугольная матрица с нулями на главной диагонали, содержащая расстояния между точками\n\n

			  a b c ...

		  a   0
		  b   # 0
		  c   # # 0
		 ...  # # # ...
	\n
	\param points массив точек
	\param size количество точек
	\return матрица расстояний
**/
double** initDistances(const Point* points, size_t size);

/**
	Вычислить центр окружности по лежащей на окружности точке, углу и радиусу
	\param position указатель на позицию центра окружности относительно точки
	\param point указатель на точку
	\param radius радиус окружности
	\return центр окружности
**/
Point getCircleCenter(const Position* position, const Point* point, int radius);

/**
	Найти центр окружности заданного радиуа, содержащей максимальное количество точек
	\param[in] points массив точек
	\param[out] optimalPoint указатель на точку, куда будет произведена запись данных о центре окружности
	\param[in] size количество точек
	\param[in] radius радиус окружности
	\return количество точек внутри окружности
**/
size_t calculateTarget(const Point* points, Point* optimalPoint, size_t size, int radius);

#endif