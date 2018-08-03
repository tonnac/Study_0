#include <stdio.h>

int main(void)
{
	int i;
	for (i = 0;i <= 100;i++)
	{
		if (i == 51)
		{
			break;
		}
		printf("%d\n", i);
	}
	return 0;
}