#include <stdio.h>
main()
{
	double a, b, c;
	a = b = c = 55.0;
	printf("%f\t%f\t%f\t", a, b, c);
	c = a + b;
	printf("%f\n", c);
	c = -c;
	printf("%2.2f\n", c);
	a = a / b;
	printf("%2.2f\n", a);
}
