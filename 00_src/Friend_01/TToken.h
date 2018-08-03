#pragma once
#include "TValue.h"

class TValue;

class TToken
{
private:
	static int iCounter;
	TValue * p1;
public:
	void Show()
	{
		TValue * temp = p1;
		do {
			std::cout << temp->pChar << std::endl;
			temp = temp->pNext;
		} while (temp != NULL);
	}
	TToken(char * data);
	~TToken();
};