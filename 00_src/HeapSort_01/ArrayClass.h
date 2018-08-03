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
	void QuickSort1(const int& start, const int& end);
	void QuickSort(const int& start, const int& end);
	void HeapSort(void);
	bool Swap(int&a, int&b, bool flag);
	void PrintData(void);
	const int& getLength(void);
	void inputHeap(const int& data);
	ArrayClass(int len);
	~ArrayClass();
	void RebuildHeap();
private:
	//void RebuildHeap();
	void BuildHeap();
	int Partition(const int& start, const int& end);
	void MergeTwoArea(const int& start, const int& mid, const int& end);
	int SearchMinidx(const int& start);
	void SetData(void);
	int * ptr;
	int length;
	int idx;
};

