#include "TValue.h"

TValue::TValue(char * data)
{
	pChar = new char[strlen(data) + 1];
	strcpy(pChar, data);
	pNext = NULL;
}

TValue::~TValue()
{
	delete[]pChar;
}