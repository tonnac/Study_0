#include "TPoint.h"

int TPoint::m_iCount = 0;

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
void TPoint::Show(void) const
{
	std::cout
		<< x
		<< " "
		<< y
		<< " "
		<< std::endl;
}
TPoint::TPoint(int _x, int _y, int _z)
{
	m_iCount++;
	this->x = _x;
	this->y = _y;
	z = new int;
	*(this->z) = _z;
}

TPoint::TPoint()
{
	m_iCount++;
	this->x = 0;
	this->y = 0;
	z = new int;
}

TPoint::TPoint(const TPoint &data)    // 복사생성자
{
	m_iCount++;
	x = data.x;
	y = data.y;
	z = new int;
	*z = *data.z;
}

int TPoint::GetCount(TPoint& a)
{
	a.Show();
	return TPoint::m_iCount;
}

TPoint::~TPoint()
{
	std::cout << "TPoint::~TPoint" << std::endl;
}