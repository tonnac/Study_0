#include <stdio.h>

int main(void)
{
	int a = 1;
	int total = 0;

	while (a <= 100)
	{
		total += a;
		a++;
	}
	printf("%d\n", total);
	return 0;
}