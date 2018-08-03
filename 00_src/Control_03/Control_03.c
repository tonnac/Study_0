#include <stdio.h>
void draw(int row, int col);

int main(void)
{
	int row, col;
	printf("행렬의 차원을 입력합니다.\n");
	printf("x = ");
	scanf("%d", &row);
	printf("y = ");
	scanf("%d", &col);

	draw(row, col);
	return 0;
}

void draw(int row, int col)
{
	int temp = col;
	for(;row > 0;row--)
	{
		for (; col > 0;col--)
			printf("x");
		col = temp;
		printf("\n");
	}
}