#pragma once
#include "Parent.h"

class Child : public Parent
{
public:
	Child() : Parent(1000)
	{
		cout << "Child ������" << endl;
	}
	~Child();
	void Humanity();
	void Character();
	void Appearance();
};

