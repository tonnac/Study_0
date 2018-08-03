#include <stdio.h>

void func(int data)
{
	data = 10;
}

int main(void)
{
	int var = 1;
	func(var);
	printf("%d\n", var);
	return 0;
}