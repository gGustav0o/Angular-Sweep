/**
	\file
	\brief ������� ���������� �������.
**/

#ifndef VECTOR_H
#define VECTOR_H

#define CVECTOR_INIT_CAPACITY 16

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "Errors.h"

/** @struct Vector
	������
	@var Vector::data
		��������� �� ������ ��������� �������
	@var Vector::size
		���������� ��������� � �������
	@var Vector::capacity
		�������� ������ ������� � ���������.
	@var Vector::elementSize
		������ �������� � ������
 **/
typedef struct
{
	void** data;
	size_t size;
	size_t capacity;
	size_t elementSize;
} Vector;

/**
	������������� �������
	\param vector ��������� �� ������
	\param elementSize ������ �������� ������� � ������
	\return 1, ���� ������������� ������ ��� ������, � ��������� ������ - 0
**/
int vectorInit(Vector* vector, size_t elementSize);

/**
	�������� ������ �������
	\param vector ��������� �� ������
	\return ���������� ��������� � �������
**/
size_t vectorGetSize(const Vector* vector);

/**
	�������� ������� � ������
	\param vector ��������� �� ������
	\param element ����������� �������
	\return 1, ���� ���������� ������ ��� ������, � ��������� ������ - 0
**/
int vectorPush(Vector* vector, const void* element);

/**
	�������� ������� �������
	\param vector ��������� �� ������
	\param index ������ ����������� ��������
	\param element ��������� �� ����� �������
	\return 1, ���� ��������� ������ ��� ������, � ��������� ������ - 0
**/
int vectorSetElement(Vector* vector, size_t index, void* element);

/**
	������� ������� �������
	\param vector ��������� �� ������
	\param index ������ ���������� ��������
	\return 1, ���� �������� ������ ��� ������, � ��������� ������ - 0
**/
int vectorDeleteElement(Vector* vector, size_t index);

/**
	�������� ������� �������
	\param vector ��������� �� ������
	\param index ������ ��������
	\return ��������� �� ������ �������
**/
void* vectorGetElement(Vector* vector, size_t index);

/**
	�������� �������� ������ ������� (capacity)
	\param vector ��������� �� ������
	\param capasity ����� ������ �������
	\return 1, ���� ��������� ������� ������ ��� ������, � ��������� ������ - 0
**/
int vectorResize(Vector* vector, size_t capasity);

/**
	�������� ������
	���������� ������, ���������� ��� �������� �������
	\param vector ��������� �� ������
**/
void vectorClear(Vector* vector);

/**
	������������� ������
	\param vector ��������� �� ������
	\param compare ��������� �� ������� ��������� ��������� �������
**/
void vectorSort(Vector* vector, int (*compare) (const void*, const void*));


#endif
