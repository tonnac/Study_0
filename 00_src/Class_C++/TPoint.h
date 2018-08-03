#pragma once
#include <iostream>
#include <conio.h>

class TPoint
{
private:
	int x;
	int y;
public:
	
	static int m_iCount;
	int * z;
	static int GetCount(TPoint& a);

	void SetPosition(int i, int j);
	void Move(int i, int j);
	// ������� �� ���� �Ұ�
	void Show() const;
	TPoint();
	TPoint(int _x, int _y, int _z);
	TPoint(const TPoint &data);
	~TPoint();
};