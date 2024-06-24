/**
	\file
	\brief ������������ ���� ������, � ������� ������������ ��������.

	Angular Sweep\n
	Time Complexity: O(n*n*lon(n))\n\n

	� ���� ����� ����������� ������� � ���������, ������������ ��� ��������.\n
	������ ��������� �������� ������� ���������. 
**/

#ifndef ARTILLERY_CALCULATOR_H
#define ARTILLERY_CALCULATOR_H

#include <stdio.h>
#include <math.h>
#include "Errors.h"
#include "Vector.h"

/** @struct Point
	����� � ��������� ���������� �����������
	@var Point::x
		x-����������
	@var Point::y
		y-����������
 **/
typedef struct {
	double x, y;
} Point;

/** @struct Position
	��������� ��������� �����.\n
	������ ���������� � �����, ������������ ������� �� ������ ���������, ��������, ������ ��������� ����� ���������� �������� ����� ������������ ��� X. 
	@var Position::angle
		���� ������������ ��� X
	@var Position::entered
		����, ������������, ����� ����� � ���������� ��� ����� �� ���
 **/
typedef struct {
	double    angle;
	short     entered;
} Position;

/**
	������� ��������� ������� ����� ��� ����������
	\param p, q ��������� �� �������
	\return 1, ���� ���� ������� p ������ ���� ������� q, � ���� ����� - -1
**/
int comparePositions(const void* p, const void* q);

/**
	���������� ��������� ���������� ����� �������
	\param a, b ��������� �� �����
	\return ���������� ����� ������� � ��������� ���������� ������������
**/
double getDistance(const Point* a, const Point* b);

/**
	���������� ���������� ����� ����� ������� �������
	\param[in] points ������ �����
	\param[out] distances ��������� �� ������� ����������
	\param[in] pointsNumber ���������� �����
	\return 1, ���� ������� ������ ��� ������, � ��������� ������ - 0
**/
int calculateDistances(const Point* points, double** distances, size_t pointsNumber);

/**
	�������� ������� ���������. ���������� ��������� ��������� ����������, ���������� �������� �����.
	\param[in] pointIndex ������ ����� � ������
	\param[in] radius ������ ����������
	\param[in] size ���������� �����
	\param[in] distances ������� ���������� ����� �������
	\param[in] points ������ �����
	\param[out] ��������� ������� ������ ���������� ������������ �������� �����
	\return ���������� �����, �������� � ����������, � ��������� �������
**/
int getPointsInside(size_t pointIndex, int radius, size_t size, const double** distances, const Point* points, Position* bestPosition);

/**
	������� ������� ���������� ����� �������\n
	��������� ����������������� ������� � ������ �� ������� ���������, ���������� ���������� ����� �������\n\n

			  a b c ...

		  a   0
		  b   # 0
		  c   # # 0
		 ...  # # # ...
	\n
	\param points ������ �����
	\param size ���������� �����
	\return ������� ����������
**/
double** initDistances(const Point* points, size_t size);

/**
	��������� ����� ���������� �� ������� �� ���������� �����, ���� � �������
	\param position ��������� �� ������� ������ ���������� ������������ �����
	\param point ��������� �� �����
	\param radius ������ ����������
	\return ����� ����������
**/
Point getCircleCenter(const Position* position, const Point* point, int radius);

/**
	����� ����� ���������� ��������� ������, ���������� ������������ ���������� �����
	\param[in] points ������ �����
	\param[out] optimalPoint ��������� �� �����, ���� ����� ����������� ������ ������ � ������ ����������
	\param[in] size ���������� �����
	\param[in] radius ������ ����������
	\return ���������� ����� ������ ����������
**/
size_t calculateTarget(const Point* points, Point* optimalPoint, size_t size, int radius);

#endif