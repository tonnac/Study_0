#include <stdio.h>

void hanoi(int n, char A, char B, char C);

int main(void)
{
	int num;
	printf("정수 입력: ");scanf("%d", &num);
	hanoi(num, 'A', 'B', 'C');

	return 0;
}

void hanoi(int n, char A, char B, char C)
{
	static int a = 0;
	if (n == 1)
	{
		printf("[%d]%c->%c\n", ++a, A, C);
	}
	else
	{
		hanoi(n - 1, A, C, B);
		printf("[%d]%c->%c\n", ++a, A, C);
		hanoi(n - 1, B, A, C);
	}
}