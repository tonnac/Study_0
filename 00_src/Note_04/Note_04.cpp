#include "Header.h"
#include <iostream>
#include <list>
using namespace std;

int main()
{
	List<int> pl;
	pl.push_back(2);
	pl.push_back(3);
	pl.push_back(4);
	pl.push_back(5);
	pl.push_back(6);
	
	List<int>::iterator iter;
	
	iter = pl.begin();
	
	for (; iter != pl.end(); iter++)
	{
		cout << *iter << endl;
	}

	return 0;
}