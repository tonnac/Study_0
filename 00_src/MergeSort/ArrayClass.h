#pragma once
#include <ctime>
#include <functional>
class ArrayClass
{
public:
	void BubbleSort(void);
	void SelectionSort(void);
	void InsertionSort(int gap=1, int start=1);
	void ShellSort(void);
	void MergeSort(const int& start, const int& end);
	bool Swap(int&a, int&b, bool flag);
	void PrintData(void);
	const int& getLength(void);
	ArrayClass(int len);
	~ArrayClass();
private:
	void MergeTwoArea(const int& start, const int& mid, const int& end);
	int SearchMinidx(const int& start);
	void SetData(void);
	int * ptr;
	int length;
};

