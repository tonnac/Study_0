#include <stdio.h>
int x = 1;
int y = 2;
void demo(void);

int main(void)
{
	printf("Before : x=%d, y=%d\n", x, y);
	demo();
	printf("After : x=%d, y=%d\n", x, y);
	return 0;
}

void demo(void)
{
	int x = 88;
	int y = 99;
	printf("In demo() : x=%d, y=%d\n", x, y);
}