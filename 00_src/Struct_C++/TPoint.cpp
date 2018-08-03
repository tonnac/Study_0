#include "TPoint.h"

void TPoint::SetPosition(int i, int j)
{
	x = i;
	y = j;
}
void TPoint::Move(int i, int j)
{
	x += i;
	y += j;
}
void TPoint::Show(void)
{
	std::cout
		<< x
		<< " "
		<< y
		<< std::endl;
}
TPoint::TPoint()
{
	x = 0;
	y = 0;
}
TPoint::~TPoint()
{
	std::cout << "TPoint::~TPoint" << std::endl;
}
