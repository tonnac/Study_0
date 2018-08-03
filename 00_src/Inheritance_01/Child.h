#pragma once
#include "Parent.h"

class Child : public Parent
{
public:
	Child() : Parent(1000)
	{
		cout << "Child »ý¼ºÀÚ" << endl;
	}
	~Child();
	void Humanity();
	void Character();
	void Appearance();
};

