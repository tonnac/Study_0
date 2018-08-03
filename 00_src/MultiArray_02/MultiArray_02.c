#include <stdio.h>

int main(void)
{
	int i, j;
	static int integer[2][3] = { 1,2,3,4,5 };

	for (i = 0;i < 2;i++)
	{
		for (j = 0;j < 3;j++)
		{
			printf("\n integer[%d][%d]=%d", i, j, integer[i][j]);
		}
	}
	return 0;
}