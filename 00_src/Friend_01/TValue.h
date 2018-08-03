#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>


class TToken;

class TValue
{
public:
private:
	friend class TToken;
	TValue(char * data);
	~TValue();
	char * pChar;
	TValue * pNext;
};