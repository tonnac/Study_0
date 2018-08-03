#include <stdio.h>

void func(int data[])
{
	data[0] = 10;
}

int main(void)
{
	int i;
	int var[10] = { 1,2,3,4,5,6,7,8,9,0 };

	func(var);
	for (i = 0;i < 10;i++)
	{
		printf("%d\n", var[i]);
	}
	return 0;
}