#include <Windows.h>
#include <iostream>

int main(void)
{
	LARGE_INTEGER Frequency;
	LARGE_INTEGER Be;
	LARGE_INTEGER Cu;
	QueryPerformanceFrequency(&Frequency);

	size_t i;
	QueryPerformanceCounter(&Be);
	for (i = 0; i < pow(2,32); ++i)
	{
		
	}

	QueryPerformanceCounter(&Cu);

	double e = (Cu.QuadPart - Be.QuadPart) / static_cast<double>(Frequency.QuadPart);

	return 0;
}