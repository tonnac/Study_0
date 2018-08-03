#include <stdio.h>

int main(void)
{
	int arr[10] = { 0,1,2,3,4,5,6,7 };
	int i, *ptr, *ptr1;
	ptr = arr;
	ptr1 = &arr[5];
	printf("Difference : %d\n", ptr1 - ptr);
	printf("Compare : %d\n", ptr > ptr1);
	for (i = 0;i < 10;i++)
	{
		printf("%d\t", *ptr++);
	}
	return 0;
}