#pragma once
#include <ctime>
class ArrayClass
{
public:
	void BubbleSort();
	bool Swap(int&a, int&b, bool flag);
	void PrintData(void);
	ArrayClass(int len);
	~ArrayClass();
	int * ptr;
	int length;
private:
	
	void SetData(void);
};

