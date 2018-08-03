#include "LLLinked.h"
#include <iostream>
#include <ctime>


int main()
{
	srand((unsigned int)time(NULL));
	LLLinked ld;

	ld.Sortrule(&LLLinked::DesSearchNode);

	for (int i = 0; i < 15; i++)
	{
		ld.push(*new LList(rand() % 55));
	}

	for (int i = 0; i < 15; i++)
	{
		ld.push(rand()%93);
	}

	ld.Show();

	return 0;
}