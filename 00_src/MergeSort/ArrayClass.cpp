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
ArrayClass::ArrayClass(int len) : length(len)
{
	ptr = new int[length];
	SetData();
}
ArrayClass::~ArrayClass()
{
	delete[] ptr;
}
void ArrayClass::SetData(void)
{
	for (int i = 0; i < length; i++)
	{
		ptr[i] = rand() % 1000;
	}
}