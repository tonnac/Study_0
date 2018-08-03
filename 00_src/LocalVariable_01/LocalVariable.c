#include <stdio.h>

void func(void);

int main(void)
{
	int count;
	for (count = 0;count < 10;count++)
	{
		printf("At iteration %d :", count);
		func();
	}
	return 0;
}

void func(void)
{
	static int x = 0;
	int y = 0;
	printf("x=%d,y=%d\n", x++, y++);
	return 0;
}