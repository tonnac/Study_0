#include "ArrayClass.h"
#include <ctime>
#include <iostream>

int main()
{

	srand((unsigned int)time(NULL));

	ArrayClass p1(15);
	p1.PrintData();

	p1.SelectionSort();

	p1.PrintData();

	return 0;
}