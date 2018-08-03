#include <stdio.h>

int main(void)
{
	int a;
	int b;
//	int c;
	int d;
	scanf_s("%d", &a);
	d = 2 * a - 1;
	for (int i = 0;i < a;i++)
	{
		b = d / 2 - i;
//		c = d / 2 + i;
		for (int j = 0;j < b;j++)
		{
			printf(" ");
		}
		for (int j = 0;j <= 2*i;j++)
		{
			printf("*");
		}
		puts("");
	}

	for (int i = a-2;i >=0 ;i--)
	{
		b = d / 2 - i;
//		c = d / 2 + i;
		for (int j = 0;j < b;j++)
		{
			printf(" ");
		}
		for (int j = 0;j <= 2*i;j++)
		{
			printf("*");
		}
		puts("");
	}
/*
	for (int i = 0;i < a - 1;i++)
	{
		b = d / 2 - i;
		//		c = d / 2 + i;
		for (int j = 0;j < i + 1;j++)
		{
			printf(" ");
		}
		for (int j = 0;j < (2 * a) - 3 - (2 * i);j++)
		{
			printf("*");
		}
		puts("");
	}
*/
	return 0;
}