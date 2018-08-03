#include <stdio.h>

int main(void)
{
	char word[] = "Happy Birth day";
	char * great = "hello";
	int count = 0;
	while (word[count] != NULL)
	{
		count++;
	}
	printf("Length=%d\n", count);

	count = 0;
	while (great[count] != NULL)
	{
		count++;
	}
	printf("Length=%d\n", count);

	return 0;
}