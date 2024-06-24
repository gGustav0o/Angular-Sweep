#include "Errors.h"

void handleError(enum ErrorCode errorCode) {
	char* errorMessage;
	switch (errorCode)
	{
	case UNEXPECTED_NUMBER_OF_ARGUMENTS:
		errorMessage = "unexpected number of arguments";
		break;
	case FILE_OPENING_ERROR:
		errorMessage = "cannot open file";
		break;
	case MEMORY_ERROR:
		errorMessage = "momory error";
		break;
	case FILE_CLOSING_ERROR:
		errorMessage = "cannot close file";
		break;
	case FILE_READING_ERROR:
		errorMessage = "cannot read coordinates";
		break;
	case NULL_POINTER_ERROR:
		errorMessage = "nullpointer";
		break;
	case CALCULATING_ERROR:
		errorMessage = "calculating error";
		break;
	case UNEXPECTED_ARGUMENT:
		errorMessage = "unexpected argument";
		break;
	default:
		errorMessage = "unknown error";
		break;
	}

	fprintf(stderr, errorMessage);
	exit(errorCode);
}