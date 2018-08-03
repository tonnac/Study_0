#include <iostream>
#include <ctime>

using namespace std;

bool Swap(int& a, int& b)
{
	if (a > b)
	{
		int temp = a;
		a = b;
		b = temp;
		return true;
	}
	return false;
}
void DataPrint(int list[], int iNum)
{
	for (int i = 0; i < iNum; i++)
	{
		std::cout << list[i] << " ";
	}
	std::cout << std::endl << std::endl;
}
void SetData(int list[], int iNum)
{
	for (int i = 0; i < iNum; i++)
	{
		list[i] = rand() % 100;
	}
	//DataPrint(list, iNum);
}

void QuickSort(int list[], int iStart, int iEnd)
{
	int iPivot = list[iStart];
	int iBegin = iStart + 1;
	if (iBegin > iEnd)
	{
		return;
	}
	int iBeginEnd = iEnd;

	while (iBegin < iBeginEnd)
	{
		while (iPivot <= list[iBeginEnd] && iBegin < iBeginEnd)
		{
			iBeginEnd--;
		}
		while (iPivot >= list[iBegin] && iBegin < iBeginEnd)
		{
			iBegin++;
		}
		if (iBegin > iBeginEnd) break;
		Swap(list[iBegin], list[iBeginEnd]);
	}
	Swap(list[iStart], list[iBegin]);

	if(iBegin > iStart+1)
		QuickSort(list, iStart, iBegin-1);
	if(iBeginEnd < iEnd)
		QuickSort(list, iBegin+1, iEnd);
}

int main()
{
	srand((unsigned int)time(NULL));
	int item[10];	// _countof
					//int * pItem = new int[20];/  / _msize(pItem)
	for (int i = 0; i < 10; i++)
	{
		item[i] = 10 - i;
	}
	//SetData(item, _countof(item));
	DataPrint(item, _countof(item));
	clock_t sTime, eTime;
	sTime = clock();		// 1000 : 1ÃÊ;
	QuickSort(item, 0, 9);
	eTime = clock() - sTime;
	std::cout << eTime / static_cast<double>(CLK_TCK) << std::endl << std::endl;
	std::cout << "Selection" << std::endl;
	DataPrint(item, _countof(item));

	return 0;
}