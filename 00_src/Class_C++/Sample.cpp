#include "TPoint.h"

int main()
{
	int Z;
	int* pData = new int;
	*pData = 5;

	const int* pValue = pData;

	//////////////////////////////
	//���� ������ , ��� ������
	const int* aValue = pData;
	//��� ������, ���� ������
	int* const bValue = pData;
	//��� ������, ��� ������
	const int* const cValue = pData;
	//��� �Լ�
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