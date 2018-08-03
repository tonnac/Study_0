#include "Figure.h"

Figure::Figure(int x, int y, int width, int height)
{
	Move(x, y);
	Resize(width, height);
}

void Figure::Move(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Figure::Resize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Figure::Draw()
{
	cout << "Figure::Draw" << endl;
}

Figure::~Figure()
{
}
