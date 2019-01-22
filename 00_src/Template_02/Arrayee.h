#pragma once
#include <iostream>
using namespace std;
template <typename T>
class Arrayee
{
private:
	T a;
	T b;
	T c;
public:
	Arrayee(const T &value1, const T &value2, const T &value3) : a(value1), b(value2), c(value3)
	{}
	void Show()
	{
		cout << a << " " << b << " " << c << endl;
	}
};