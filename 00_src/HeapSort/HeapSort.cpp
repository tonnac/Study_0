#include <iostream>
#include <ctime>

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
void Change(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
void BuildHeap(int list[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int iChild = i;
		do
		{
			int iRoot = (iChild - 1) / 2;
			if (list[iRoot] < list[iChild])
			{
				Change(list[iRoot], list[iChild]);
			}
			iChild = iRoot;
		} while (iChild != 0);
	}
}
void RebuildHeap(int list[], int n)
{
	for (int iLast = n-1; iLast >= 0; iLast--)
	{
		Change(list[0], list[iLast]); 
		int iRoot = 0;
		int iChild;
		do
		{
			iChild = 2 * iRoot + 1;

			if (iChild < iLast - 1 &&
				list[iChild] < list[iChild+1])
			{
				iChild++;
			}
			if (iChild < iLast &&
				list[iRoot] < list[iChild])
			{
				Change(list[iRoot], list[iChild]);
			}
			iRoot = iChild;
		} while (iChild < iLast);
	}
}
void HeapSort(int list[], int n)
{
	BuildHeap(list, n);
	RebuildHeap(list, n);
}

int main()
{
	srand((unsigned int)time(NULL));
	int item[15];	// _countof
					//int * pItem = new int[20];/  / _msize(pItem)

	SetData(item, _countof(item));
	DataPrint(item, _countof(item));

	//clock_t sTime, eTime;
	//sTime = clock();		// 1000 : 1ÃÊ;
	//eTime = clock() - sTime;
	//std::cout << eTime / static_cast<double>(CLK_TCK) << std::endl << std::endl;
	//std::cout << "Selection" << std::endl;
	//DataPrint(item, _countof(item));

	HeapSort(item, _countof(item));
	DataPrint(item, _countof(item));

	return 0;
}