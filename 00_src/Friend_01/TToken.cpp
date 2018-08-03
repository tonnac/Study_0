#include "TToken.h"

int TToken::iCounter = 1;

TToken::TToken(char * data)
{
	char * temp;
	temp = strtok(data, " ");
	p1 = new TValue(temp);
	TValue * cTemp = p1;
	for (iCounter;
		(temp = strtok(NULL, " ")) != NULL;
		iCounter++)
	{
		cTemp->pNext = new TValue(temp);
		cTemp = cTemp->pNext;
	}
}

TToken::~TToken()
{
	TValue * temp = p1;
	TValue * temp1 = NULL;

	while (temp != NULL)
	{
		temp1 = temp->pNext;
		delete temp;
		temp = temp1;
	}
}