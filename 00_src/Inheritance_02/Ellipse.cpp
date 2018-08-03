#include "Ellipse.h"



Ellipse::Ellipse(int x,int y,int width,int height)
	: Figure(x,y,width,height)
{}

void Ellipse::Draw()
{
	cout << "Draw Ellipse: ";
	cout << "(" << x << "," << y << "),";
	cout << width << "x" << height;
	cout << endl;
}

Ellipse::~Ellipse()
{
}

