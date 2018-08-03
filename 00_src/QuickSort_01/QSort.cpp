#include "ArrayClass.h"
#include <ctime>
#include <iostream>


int main()
{
	srand((unsigned int)time(NULL));

	ArrayClass p1(20000);
	clock_t stime, etime;
	//	p1.PrintData();

	p1.SortTimer(p1.BubbleSort);

	stime = clock();
	p1.InsertionSort();
	//	p1.PrintData();
	etime = (clock() - stime);
	std::cout << "InsertionSort: " << etime / (double)CLK_TCK << std::endl << std::endl;

	//stime = clock();
	//p1.BubbleSort();
	//etime = (clock() - stime);
	//std::cout << "BubbleSort: " << etime / (double)CLK_TCK << std::endl << std::endl;
	////	p1.PrintData();

	stime = clock();
	p1.SelectionSort();
	etime = (clock() - stime);
	std::cout << "SelectionSort: " << etime / (double)CLK_TCK << std::endl << std::endl;
	//	p1.PrintData();

	stime = clock();
	p1.MergeSort(0, p1.getLength() - 1);
	etime = (clock() - stime);
	std::cout << "MergeSort: " << etime / (double)CLK_TCK << std::endl << std::endl;
	//	p1.PrintData();

	stime = clock();
	p1.ShellSort();
	etime = (clock() - stime);
	std::cout << "ShellSort: " << etime / (double)CLK_TCK << std::endl << std::endl;
	//p1.PrintData();

	stime = clock();
	p1.QuickSort(0, p1.getLength() - 1);
	etime = (clock() - stime);
	std::cout << "QuickSort: " << etime / (double)CLK_TCK << std::endl << std::endl;
	//p1.PrintData();

	return 0;
}