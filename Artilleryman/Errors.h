/**
	\file
	\brief Заголовочный файл обработчика ошибок

	Содержит константы кодов ошибок и объявление функции обработки ошибок.
**/

#ifndef ERROR_CODE_H
#define ERROR_CODE_H 

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// Коды ошибок
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
	Выводит сообщение об ошибке и завершает программу
	\param errorCode код ошибки
**/
void handleError(enum ErrorCode errorCode);

#endif