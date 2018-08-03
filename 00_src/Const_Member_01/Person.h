#pragma once
#include <iostream>

class Person
{
public:
	Person(int id);
	//~Person();
	void show();
private:
	const int id;
};

