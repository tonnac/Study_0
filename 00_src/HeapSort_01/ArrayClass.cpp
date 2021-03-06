#include "ArrayClass.h"
#include <iostream>

void ArrayClass::BubbleSort(void)
{
	for (int i = 0; i < length; i++)
	{
		int bflag = false;
		for (int j = 0; j < length - 1 - i; j++)
		{
			bflag += Swap(ptr[j], ptr[j + 1], ptr[j] < ptr[j + 1]);
		}
		if (bflag == false)
		{
			break;
		}
	}
}
void ArrayClass::SelectionSort(void)
{
	for (int i = 0; i < length; i++)
	{
		int idx = SearchMinidx(i);
		Swap(ptr[idx], ptr[i], 1);
	}
}
void ArrayClass::InsertionSort(int gap, int start)
{
	for (int i = start + gap; i < length; i+=gap)
	{
		int element = ptr[i];
		int j = i - gap;
		while (j >= 0 && element < ptr[j])
		{
			ptr[j + gap] = ptr[j];
			j-=gap;
		}
		ptr[j + gap] = element;
	}
}
void ArrayClass::ShellSort(void)
{
	int maxGroup;
	for (int k = 1; k < length; k++)
	{
		int g = (pow(3, k) - 1) / 2;
		if (g > length)
		{
			break;
		}
		maxGroup = k;
	};

	while (maxGroup > 0)
	{
		int g = (pow(3, maxGroup--) - 1) / 2;
		// 부분정렬 수행
		for (int s = 0; s < g; s++)
		{
			InsertionSort(g, s);
		}
	}

	//int k = length / 2;
	//while (k > 1)
	//{
	//	k /= 2;
	//	for (int i = 0; i < length; i++)
	//	{
	//		InsertionSort(k, i);
	//	}
	//}
}
void ArrayClass::MergeSort(const int& start, const int& end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		MergeSort(start, mid);
		MergeSort(mid + 1, end);

		MergeTwoArea(start, mid, end);
	}
}
void ArrayClass::MergeTwoArea(const int& start, const int& mid, const int& end)
{
	int lidx = start;
	int ridx = mid + 1;
	int sidx = start;
	int * arr = new int[end + 1];

	while (lidx <= mid && ridx <= end)
	{
		if (ptr[lidx] < ptr[ridx])
			arr[sidx++] = ptr[ridx++];
		else
			arr[sidx++] = ptr[lidx++];
	}

	if (lidx > mid)
	{
		for(;ridx<=end;ridx++, sidx++)
			arr[sidx] = ptr[ridx];
	}
	else
	{
		for (; lidx <= mid; lidx++, sidx++)
			arr[sidx] = ptr[lidx];
	}

	for (int i = start; i < sidx; i++)
	{
		ptr[i] = arr[i];
	}

	delete[]arr;
}
void ArrayClass::QuickSort1(const int& start, const int& end)
{
	if (start > end){return;}
	int iPivot = ptr[start];
	int iLeft = start + 1;
	int iRight = end;
	while (iLeft <= iRight)
	{
		while (iPivot <= ptr[iLeft] && iLeft <= iRight)
		{
			iLeft++;
		}
		while (iPivot >= ptr[iRight] && iRight >= iLeft)
		{
			iRight--;
		}
		if (iLeft <= iRight)
			Swap(ptr[iLeft], ptr[iRight], 1);
	}
	Swap(ptr[start], ptr[iRight], 1);
	QuickSort1(start, iRight - 1);
	QuickSort1(iRight + 1, end);
}
void ArrayClass::QuickSort(const int& start, const int& end)
{
	if (start <= end)
	{
		int mid = Partition(start, end);
		QuickSort(start, mid - 1);
		QuickSort(mid + 1, end);
	}
}
void ArrayClass::HeapSort(void)
{
	BuildHeap();
	RebuildHeap();
}
bool ArrayClass::Swap(int&a, int&b, bool flag)
{
	if (flag)
	{
		int temp = a;
		a = b;
		b = temp;
		return true;
	}
	return false;
}
int ArrayClass::SearchMinidx(const int& start)
{
	int Minidx = start;
	for (int i = start+1; i < length; i++)
	{
		if (ptr[Minidx] > ptr[i])
			Minidx = i;
	}
	return Minidx;
}
void ArrayClass::PrintData(void)
{
	for (int i = 0; i < length; i++)
	{
		if (i != 0)
		{
			std::cout << " ";
		}
		std::cout << ptr[i];
	}
	std::cout << std::endl;
}
const int& ArrayClass::getLength(void)
{
	return length;
}
ArrayClass::ArrayClass(int len) : length(len), idx(0)
{
	ptr = new int[length];
//	SetData();
}
ArrayClass::~ArrayClass()
{
	delete[] ptr;
}
void ArrayClass::SetData(void)
{
	for (int i = 0; i < length; i++)
	{
		ptr[i] = rand() % 100;
	}
}
int ArrayClass::Partition(const int& start, const int& end)
{
	int iPivot = ptr[start];
	int iLeft = start + 1;
	int iRight = end;
	while (iLeft <= iRight)
	{
		while (iPivot >= ptr[iLeft] && iLeft <= end)
		{
			iLeft++;
		}
		while (iPivot <= ptr[iRight] && iRight >= (start + 1))
		{
			iRight--;
		}
		if (iLeft <= iRight)
			Swap(ptr[iLeft], ptr[iRight], 1);
	}
	Swap(ptr[start], ptr[iRight], 1);
	return iRight;
}
void ArrayClass::BuildHeap()
{
	for (int i = 1; i < length; i++)
	{
		int a = i;
		do
		{
			int Parent = (a - 1) / 2;
			if (ptr[Parent] > ptr[a])
			{
				Swap(ptr[Parent], ptr[a], 1);
			}
			a = Parent;
		} while (a != 0);
	}
}
void ArrayClass::RebuildHeap()
{
	for (int i = length - 1; i >= 0; i--)
	{
		int a = 0;
		Swap(ptr[a], ptr[i], 1);
		while (a < i)
		{
			int iChild = a * 2 + 1;
			if (ptr[iChild] < ptr[iChild + 1]
				&& iChild < i - 1)
				iChild++;
			if (ptr[a] < ptr[iChild]
				&& iChild < i)
				Swap(ptr[a], ptr[iChild], 1);
			a = iChild;
		}
	}
}
void ArrayClass::inputHeap(const int& data)
{
	int a = idx;
	ptr[a] = data;
	int parent;
	do
	{
		parent = (a - 1) / 2;
		if (ptr[a] > ptr[parent])
		{
			Swap(ptr[a], ptr[parent], 1);
		}
		a = parent;
	}while (parent > 0 && parent < length);
	idx++;
}