#include <stdio.h>

void DrawDiamond(int iRow)
{
	int i, j;
	for (i = 0;i < iRow;i++)
	{
		for (j = 0;j < iRow - 1 - i;j++)
		{
			printf("-");
		}
		for (j = 0;j <= 2 * i;j++)
		{
			if (j % 2)
			{
				printf(" ");
			}
			else
			{
				printf("*");
			}
		}
		printf("\n");
	}
	for (i = iRow - 2;i >= 0;i--)
	{
		for (j = 0;j < iRow - 1 - i;j++)
		{
			printf("-");
		}
		for (j = 0;j <= 2 * i;j++)
		{
			if (j % 2)
			{
				printf(" ");
			}
			else
			{
				printf("*");
			}
		}
		printf("\n");
	}
}
int main(void)
{
	int iRow;
	scanf_s("%d", &iRow);
	DrawDiamond(iRow);
	return 0;
}
