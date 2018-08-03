#include <stdio.h>

int main(void)
{
	int arr[5], x;
	float farr[5];
	double darr[5];
	printf("\t\tInteger\t\tFloat\t\tDouble");
	for (x = 0;x < 5;x++)
	{
		printf("\nElement %d:\t%p\t\t%p\t\t%p", x, &arr[x], &farr[x], &darr[x]);
	}
}