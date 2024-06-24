/**
	\file
	\brief Простая реализация вектора.
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
	Вектор
	@var Vector::data
		Указатель на массив элементов вектора
	@var Vector::size
		Количество элементов в векторе
	@var Vector::capacity
		Реальный размер вектора в элементах.
	@var Vector::elementSize
		Размер элемента в байтах
 **/
typedef struct
{
	void** data;
	size_t size;
	size_t capacity;
	size_t elementSize;
} Vector;

/**
	Инициализация вектора
	\param vector указатель на вектор
	\param elementSize размер элемента вектора в байтах
	\return 1, если инициализация прошла без ошибок, в противном случае - 0
**/
int vectorInit(Vector* vector, size_t elementSize);

/**
	Получить размер вектора
	\param vector указатель на вектор
	\return количество элементов в векторе
**/
size_t vectorGetSize(const Vector* vector);

/**
	Добавить элемент в вектор
	\param vector указатель на вектор
	\param element добавляемый элемент
	\return 1, если добавление прошло без ошибок, в противном случае - 0
**/
int vectorPush(Vector* vector, const void* element);

/**
	Изменить элемент вектора
	\param vector указатель на вектор
	\param index индекс изменяемого элемента
	\param element указатель на новый элемент
	\return 1, если изменение прошло без ошибок, в противном случае - 0
**/
int vectorSetElement(Vector* vector, size_t index, void* element);

/**
	Удалить элемент вектора
	\param vector указатель на вектор
	\param index индекс удаляемого элемента
	\return 1, если удаление прошло без ошибок, в противном случае - 0
**/
int vectorDeleteElement(Vector* vector, size_t index);

/**
	Получить элемент вектора
	\param vector указатель на вектор
	\param index индекс элемента
	\return указатель на нужный элемент
**/
void* vectorGetElement(Vector* vector, size_t index);

/**
	Изменить реальный размер вектора (capacity)
	\param vector указатель на вектор
	\param capasity новый размер вектора
	\return 1, если изменение размера прошло без ошибок, в противном случае - 0
**/
int vectorResize(Vector* vector, size_t capasity);

/**
	Очистить вектор
	Освоождает память, выделенную под элементы вектора
	\param vector указатель на вектор
**/
void vectorClear(Vector* vector);

/**
	Отсортировать вектор
	\param vector указатель на вектор
	\param compare указатель на функцию сравнения элементов вектора
**/
void vectorSort(Vector* vector, int (*compare) (const void*, const void*));


#endif
