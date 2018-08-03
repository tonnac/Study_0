#pragma once
#include <iostream>
using namespace std;

class Figure
{
public:
	Figure(int x,int y,int width,int height);
	~Figure();
	void Move(int x, int y);
	void Resize(int width, int height);
	void Draw();

protected:
	int x;
	int y;
	int width;
	int height;
};

