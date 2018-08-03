#include <stdio.h>

#define MAX 10
int largest(int x[], int y);

int main(void)
{
	int array[MAX], count;
	for (count = 0;count < MAX;count++)
	{
		printf("Enter Number:");
		scanf("%d", &array[count]);
	}
	printf("\n\nLargest value = %d", largest(array, MAX));
	return 0;
}

int largest(int x[], int y)
{
	int count, biggest = x[0];
	for (count = 0;count < y;count++)
	{
		if (x[count] > biggest)
		{
			biggest = x[count];
		}
	}
	return biggest;
}