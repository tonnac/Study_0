#include <stdio.h>

int main(void)
{
	int a = 10;
	if (a == 10)
	{
		printf("A=10\n");
	}
	if (a)
	{
		printf("A=True\n");
	}
	if (!a)
	{
		printf("A=False\n");
	}
	return 0;
}