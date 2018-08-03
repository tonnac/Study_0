#include <stdio.h>
#define MAX 10

int main(void)
{
	int arr[MAX] = { 0,1,2,3,4,5,6,7,8,9 };
	int * ptr, count;
	ptr = arr;
	for (count = 0;count < MAX;count++)
	{
		printf("%d\n", *ptr++);
	}
	for (count = MAX - 1;count > 0;count--)
	{
		printf("%d\n", *--ptr);
	}
	return 0;
}