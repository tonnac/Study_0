#include <stdio.h>

int main(void)
{
	int a;
	{
		int b;
		a = 5;
		b = 10;
		printf("%d %d\n", a, b);
	}
	a = 10;
	printf("%d\n", a);//, b);
	return 0;
}