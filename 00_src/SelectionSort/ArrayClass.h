#pragma once
#include <ctime>
class ArrayClass
{
public:
	void BubbleSort(void);
	void SelectionSort(void);
	bool Swap(int&a, int&b, bool flag);
	void PrintData(void);
	ArrayClass(int len);
	~ArrayClass();
private:
	int SearchMinidx(const int& start);
	void SetData(void);
	int * ptr;
	int length;
};

