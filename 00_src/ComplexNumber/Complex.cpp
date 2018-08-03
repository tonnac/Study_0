#include "Complex.h"



Complex::Complex()
{
	real = 0;
	imagination = 0;
}

Complex::Complex(double _real,double _imagination)
{
	real = _real;
	imagination = _imagination;
}

Complex Complex::operator +(Complex & data)
{
	Complex temp;
	temp.real = real + data.real;
	temp.imagination = imagination + data.imagination;
	return temp;
}
Complex Complex::operator -(Complex & data)
{
	Complex temp;
	temp.real = real - data.real;
	temp.imagination = imagination - data.imagination;
	return temp;
}
Complex Complex::operator *(Complex & data)
{
	Complex temp;
	temp.real = real * data.real - imagination * data.imagination;
	temp.imagination = real * data.imagination + imagination * data.real;
	return temp;
}
Complex Complex::operator /(Complex & data)
{
	Complex temp;
	temp.real = ((real * data.real) + (imagination * data.imagination)) / ((data.real * data.real) + (data.imagination * data.imagination));
	temp.imagination = ((real * data.imagination) - (imagination * data.real)) / ((data.real * data.real) + (data.imagination * data.imagination));
	return temp;
}
Complex Complex::operator +=(Complex & data)
{
	this->real += data.real;
	this->imagination += data.imagination;
	return *this;
}
void Complex::GetNum(double _real, double _imagination)
{
	real = _real;
	imagination = _imagination;
}
void Complex::ShowNum(void)
{
	std::cout << real << "+" << imagination << "i" << std::endl;
}