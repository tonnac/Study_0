#pragma once
#include <iostream>

class TFigure
{
public:
	void Move(int x, int y);
	void Resize(int w, int h);
	void Draw();
protected:
	int m_ix;
	int m_iy;
	int m_iWidth;
	int m_iHeight;

public:
	TFigure();
	virtual ~TFigure();
};

