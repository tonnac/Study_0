#include "TPoint.h"

int main()
{
	int Z;
	int* pData = new int;
	*pData = 5;

	const int* pValue = pData;

	//////////////////////////////
	//비상수 포인터 , 상수 데이터
	const int* aValue = pData;
	//상수 포인터, 비상수 데이터
	int* const bValue = pData;
	//상수 포인터, 상수 데이터
	const int* const cValue = pData;
	//상수 함수
	//void show() const;
	//////////////////////////////


	TPoint p1(3, 5, 4);
	TPoint p2(5, 3, 7);

	std::cout << TPoint::m_iCount << std::endl;

	p1.SetPosition(10, 10);
	*p1.z = 10;

	
	p2 = p1;

	p2.Show();


	/*p2.SetPosition(30, 30);
	p1.Move(10, 10);
	p1.Show();
	p2.Move(10, 10);
	p2.Show();*/
}