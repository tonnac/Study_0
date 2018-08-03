#include "ArrayClass.h"
#include <iostream>

void ArrayClass::BubbleSort(void)
{
	for (int i = 0; i < length; i++)
	{
		int bflag = false;
		for (int j = 0; j < length - 1 - i; j++)
		{
			bflag += Swap(ptr[j], ptr[j + 1], ptr[j] > ptr[j + 1]);
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
	int k = length / 2;
	while (k > 1)
	{
		k /= 2;
		for (int i = 0; i < length; i++)
		{
			InsertionSort(k, i);
		}
	}
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