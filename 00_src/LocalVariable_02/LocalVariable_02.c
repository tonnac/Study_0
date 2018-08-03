#include <stdio.h>

int main(void)
{
	int count = 0;
	printf("Out,count=%d\n", count);
	{
		int count = 99;
		printf("In,count=%d\n", count);
	}
	printf("Out,count=%d\n", count);
	return 0;
}