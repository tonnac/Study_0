#pragma once
#include <iostream>

class Complex
{
public:
	Complex();
	Complex(double real, double imagination);
	void GetNum(double real, double imagination);
	void ShowNum(void);
public:
	Complex operator +(Complex & data);
	Complex operator -(Complex & data);
	Complex operator *(Complex & data);
	Complex operator /(Complex & data);
	Complex operator +=(Complex & data);
private:
	double real;
	double imagination;
};

