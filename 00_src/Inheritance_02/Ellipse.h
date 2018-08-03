#pragma once
#include "Figure.h"

class Ellipse : public Figure
{
public:
	Ellipse(int x, int y,int width,int height);
	~Ellipse();
	void Draw();
};

