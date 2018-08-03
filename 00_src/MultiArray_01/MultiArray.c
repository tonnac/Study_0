#include <stdio.h>

int main(void)
{
	int a[2][3];
	int i, j;

	a[0][0] = 0; a[0][1] = 1; a[0][2] = 2;
	a[1][0] = 1; a[1][1] = 2; a[1][2] = 3;

	printf("\n A[%d][%d]=%d", 0, 0, a[0][0]);
	printf("\n A[%d][%d]=%d", 0, 1, a[0][1]);
	printf("\n A[%d][%d]=%d", 0, 2, a[0][2]);
	printf("\n A[%d][%d]=%d", 1, 0, a[1][0]);
	printf("\n A[%d][%d]=%d", 1, 1, a[1][1]);
	printf("\n A[%d][%d]=%d", 1, 2, a[1][2]);

	return 0;
}