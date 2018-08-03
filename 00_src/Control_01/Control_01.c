#include <stdio.h>

int main(void)
{
	int oddTotal = 0, evenTotal = 0;
	for (int I = 1;I <= 100;I++)
	{
		if (I % 2 == 0)
			evenTotal += I;
		else
			oddTotal += I;
	}
	printf("%d %d\n", evenTotal, oddTotal);
	return 0;
}