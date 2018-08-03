#include <stdio.h>

int main(void)
{
	int iSum = 0;
	int i = 0;
	for (i = 0; i <= 100; i++)
	{
		iSum += i;
	}
	iSum = 0;
	i = 0;
	while (i <= 100)
	{
		iSum += i++;
	}
	iSum = 0;
	i = 0;
	do
	{
		iSum += i++;
	} while (i <= 100);
	printf("%d\n", iSum);
	return 0;
}
