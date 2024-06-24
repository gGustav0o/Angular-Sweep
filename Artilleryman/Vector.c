#include "Vector.h"

int vectorInit(Vector* vector, size_t dataSize) {
	vector->capacity = CVECTOR_INIT_CAPACITY;
	vector->size = 0;
	vector->elementSize = dataSize;
	vector->data = (void**)malloc(CVECTOR_INIT_CAPACITY * sizeof(void*));
	if (!vector->data)
		return 0;
	return 1;
}

size_t vectorGetSize(const Vector* vector) {
	return vector->size;
}

int vectorPush(Vector* vector, const void* data) {
	if (vector->size >= vector->capacity) {
		if (!vectorResize(vector, vector->capacity + vector->capacity / 2))
			return 0;
	}

	vector->data[vector->size] = (void*)malloc(vector->elementSize);
	if (!(vector->data[vector->size]))
		return 0;
	else {
		memcpy(vector->data[vector->size], data, vector->elementSize);
		vector->size++;
		return 1;
	}
}

int vectorSetElement(Vector* vector, size_t index, void* data) {
	if (index >= 0 && index < vector->size && vector) {
		memcpy(vector->data[index], data, vector->elementSize);
		return 1;
	}
	return 0;
}

int vectorDeleteElement(Vector* vector, size_t index) {
	if (index < 0 || index > vector->size - 1 || vector->size <= 0)
		return 0;

	free(vectorGetElement(vector, index));

	for (size_t i = index; i < vector->size - 1; i++)
		vector->data[i] = vector->data[i + 1];

	if (vectorResize(vector, vector->size - 1)) {
		vector->size--;
		return 1;
	}
	else
		return 0;
}

void* vectorGetElement(Vector* vector, size_t index) {
	if (index < 0 || index > vector->size - 1 || vector->size <= 0)
		return NULL;

	return vector->data[index];
}

void vectorClear(Vector* vector) {
	for (int i = 0; i < vector->size; i++)
		free(vector->data[i]);
	vector->size = 0;
	free(vector->data);
}

int vectorResize(Vector* vector, size_t capasity) {
	vector->capacity = capasity;
	void** temp = realloc(vector->data, capasity * sizeof(void*));
	if (temp) {
		vector->data = temp;
		return 1;
	}
	else
		return 0;
}

void vectorSort(Vector* vector, int (*compare) (const void*, const void*)) {
	qsort(vector->data, vector->size, sizeof(void*), compare);
}