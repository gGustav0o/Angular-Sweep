/**
	\file
	\brief ������������ ���� ����������� ������

	�������� ��������� ����� ������ � ���������� ������� ��������� ������.
**/

#ifndef ERROR_CODE_H
#define ERROR_CODE_H 

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// ���� ������
enum ErrorCode {
	UNEXPECTED_NUMBER_OF_ARGUMENTS
	, FILE_OPENING_ERROR
	, FILE_CLOSING_ERROR
	, FILE_READING_ERROR
	, MEMORY_ERROR
	, NULL_POINTER_ERROR
	, CALCULATING_ERROR
	, UNEXPECTED_ARGUMENT
};


/**
	������� ��������� �� ������ � ��������� ���������
	\param errorCode ��� ������
**/
void handleError(enum ErrorCode errorCode);

#endif