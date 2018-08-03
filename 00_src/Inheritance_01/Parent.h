#pragma once
#include <iostream>

using namespace std;

class Parent
{
public:
	Parent() : money(1000000000)
	{
		cout << "Parent ������" << endl;
	}
	Parent(int _money) : money(_money)
	{
		cout << "Parent ������" << endl;
	}
	~Parent();
	void Character();
	void Appearance();
	void Wealth();
private:
	int money;
};

