#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int** ArrayAllocation(int n);
int** MagicSquare(int m);
void ShowMagicSquare(int ** ptr, int n);

int main(void)
{
	int num;
	int ** Array;
	printf("È¦¼ö ÀÔ·Â: ");scanf("%d", &num);
	Array = MagicSquare(num);
	ShowMagicSquare(Array, num);
	return 0;
}


int** ArrayAllocation(int n)
{
	int ** Array;
	Array = (int**)calloc(n,sizeof(intptr_t));

	for (int iCnt = 0;iCnt < n;iCnt++)
	{
		Array[iCnt] = (int*)calloc(n, sizeof(intptr_t));
	}

	return Array;
}
int** MagicSquare(int n)
{
	int ** ptr = ArrayAllocation(n);
	int num = 1;
	int x = (n - 1) / 2;
	int y = 0;
	ptr[y][x] = num++;
	do
	{
		if ((y - 1) < 0 && (x + 1) >= n)
		{
			ptr[++y][x] = num++;
		}
		else if ((y - 1) < 0)
		{
			y = n - 1;
			ptr[y][++x] = num++;
		}
		else if ((x + 1) >= n)
		{
			x = 0;
			ptr[--y][x] = num++;
		}
		else
		{
			if (ptr[y - 1][x + 1])
			{
				ptr[++y][x] = num++;
			}
			else
			{
				ptr[--y][++x] = num++;
			}
		}
	} while (num <= n * n);

	return ptr;
}
void ShowMagicSquare(int ** ptr, int n)
{
	for (int iCnt = 0; iCnt < n;iCnt++)
	{
		for (int jCnt = 0; jCnt < n; jCnt++)
		{
			printf("%3d ", ptr[iCnt][jCnt]);
		}
		puts("");
	}

	for (int iCnt = 0;iCnt < n;iCnt++)
	{
		free(ptr[iCnt]);
	}
	free(ptr);
}