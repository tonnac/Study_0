#include <stdio.h>
int index, arr[10];

int main(void)
{
	for (index = 0;index < 10;index++)
	{
		scanf("%d", &arr[index]);
	}
	for (index = 0;index < 10;index++)
	{
		printf("%d:%d\n", index, arr[index]);
	}
	return 0;
}