#include <stdio.h>

int main(void)
{
	int a;
	scanf_s("%d", &a);
	for (int i = 1; i <= a; i++)
	{
		for (int j = 1; j <= a; j++)
		{
			if (j == a - i + 1)
			{
				printf("*");
			}
			else if (j > a - i + 1)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		for (int j = 1; j <= a - 1; j++)
			if (j == i - 1)
			{
				printf("*");
			}
			else if (j < i - 1)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		printf("\n");
	}
	for (int i = 1; i <= a - 1; i++)
	{
		for (int j = 1; j <= a; j++)
		{
			if (j == i + 1)
			{
				printf("*");
			}
			else if (j > i + 1)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		for (int j = 1; j <= a - 1; j++)
			if (j == a - i - 1)
			{
				printf("*");
			}
			else if (j < a - i - 1)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		printf("\n");
	}
	return 0;
}