#include <iostream>
#include "Complex.h"


int main()
{
	Complex a(10, 10);
	Complex b(25, 15);
	Complex c(15, 15);
	Complex d;
	d = a + b + c;
	d.ShowNum();
}