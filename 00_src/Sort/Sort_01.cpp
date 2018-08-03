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
bool Swap1(int& a, int& b)
{
	if (a < b)
	{
		int temp = a;
		a = b;
		b = temp;
		return true;
	}
	return false;
}
void SelectionSort(int list[], int iNum)
{
	for (int i = 0; i < iNum; i++)
	{
		for (int j = i+1; j < iNum; j++)
		{
			Swap(list[i], list[j]);
		}
	}
}
void BubbleSort(int list[], int iNum)
{
	for (int i = 0; i < iNum-1; i++)
	{
		bool bflag = false;
		for (int j = 0; j < iNum-1-i; j++)
		{
			bflag = Swap1(list[j], list[j + 1]);
		}
		if (bflag == false)
		{
			break;
		}
	}
}
void InsertionSort(int list[], int iNum, int s=1, int step=1)
{
	int j;
	for (int i = s; i < iNum; i+=step)
	{
		int temp = list[i];
		for (j = i-step; j >=0 ; j-=step)
		{
			if (list[j] > temp)
			{
				list[j + step] = list[j];
			}
			else
			{
				break;
			}
		}
		list[j + step] = temp;
	}
}
void InsertionSort1(int list[], int iNum, int s = 1, int step = 1)
{
	int j;
	for (int i = s; i < iNum; i += step)
	{
		int temp = list[i];
		for (j = i - step; j >= 0; j -= step)
		{
			if (list[j] < temp)
			{
				list[j + step] = list[j];
			}
			else
			{
				break;
			}
		}
		list[j + step] = temp;
	}
}
void ShellSort(int list[], int iNum)
{

	int k = 8; // 그룹의 개수
	k = iNum / 2; // 일반적

	while (k > 1)
	{
		k = k / 2;
		for (int s = 0; s < k; s++)
		{						 //시작,간격
			InsertionSort(list,iNum, s, k);
		}
	}
	//////////////////////Best Gap////////////////////////////
	// g = 3 * x + 1;
	// x = (n-1) / 3;
	//int g;
	//for (g = 1; g < iNum; g = 3 * g + 1);
	//for (g /= 3; g > 0; g /= 3);
	///g = g /= 3;				최적의 간격.
	//for(g/=3; g>0; g/=3)
	//{
		//for (int i = 0; i < g; i++)
		//{
			//	g = g /= 3;
			//	for (int i = 0; s < g; i++)
			//	{						
			//		InsertionSort(list, iNum, i+g, g);
			//	}
		//}
	//}
}

int main()
{
	srand((unsigned int)time(NULL));
	int item[15];	// _countof
	//int * pItem = new int[20];/  / _msize(pItem)
	SetData(item, _countof(item));
	clock_t sTime, eTime;
	sTime = clock();		// 1000 : 1초;
	SelectionSort(item, _countof(item));
	eTime = clock() - sTime;
	std::cout << eTime / static_cast<double>(CLK_TCK) << std::endl << std::endl;
	std::cout << "Selection" << std::endl;
	DataPrint(item, _countof(item));

	sTime = clock();		// 1000 : 1초;
	BubbleSort(item, _countof(item));
	eTime = clock() - sTime;
	std::cout << eTime / static_cast<double>(CLK_TCK) << std::endl << std::endl;
	std::cout << "Bubble" << std::endl;
	DataPrint(item, _countof(item));

//	sTime = clock();		// 1000 : 1초;
//	InsertionSort(item, _countof(item));
//	eTime = clock() - sTime;
//	std::cout << eTime / static_cast<double>(CLK_TCK) << std::endl << std::endl;
//	DataPrint(item, _countof(item));

	InsertionSort1(item, _countof(item));
	std::cout << "Insertion" << std::endl;
	DataPrint(item, _countof(item));

	sTime = clock();		// 1000 : 1초;
	ShellSort(item, _countof(item));
	eTime = clock() - sTime;
	std::cout << eTime / static_cast<double>(CLK_TCK) << std::endl << std::endl;
	std::cout << "Shell" << std::endl;
	DataPrint(item, _countof(item));

	return 0;
}