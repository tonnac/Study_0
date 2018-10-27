#include <windows.h>
#include <cstdint>
#include <iostream>

int main()
{
	__int64 dl;
	QueryPerformanceFrequency((LARGE_INTEGER*)&dl);
	double mTimetick = 1 / (double)dl;

	__int64 buft;
	QueryPerformanceCounter((LARGE_INTEGER*)&buft);

	for (UINT i = 0; i < pow(2, 27); ++i)
	{

	}
	
	__int64 aft;
	QueryPerformanceCounter((LARGE_INTEGER*)&aft);

	std::cout << "Elapsed Time : " << (aft - buft) * mTimetick << std::endl;

	return 0;
}