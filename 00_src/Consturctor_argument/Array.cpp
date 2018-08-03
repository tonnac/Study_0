#include "Array.h"



Array::Array()
{
	maxsize = 100;
	pData = new int[maxsize];
}

Array::Array(int size)
{
	maxsize = size;
	pData = new int[maxsize];
}

Array::~Array()
{
	delete[] pData;
}

bool Array::SetData(int pos, int data)
{
	if (pos < 0 || pos >= maxsize)
	{
		return false;
	}
	pData[pos] = data;
	return true;
}

bool Array::GetData(int pos, int &data)
{
	if (pos < 0 || pos >= maxsize)
	{
		return false;
	}
	data = pData[pos];
	return true;
}