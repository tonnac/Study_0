#pragma once
#include <iostream>

class TPoint
{
private:
	int x;
	int y;
public:
	void SetPosition(int i, int j);
	void Move(int i, int j);
	void Show();
	TPoint();
	~TPoint();
};