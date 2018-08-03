#include <stdio.h>
#include <ctype.h>
int main(void)
{
	int i;
	printf("\n--------------------  Alpha  --------------------\n");
	for (i = 0; i<128; i++)
	{
		if (isalpha(i))
			printf("%d %c\t", i, i);
	}
	printf("\n\n--------------------  Upper  --------------------\n");
	for (i = 0; i<128; i++)
	{
		if (isupper(i))
			printf("%d %c\t", i, i);
	}
	printf("\n\n--------------------  Lower  --------------------\n");
	for (i = 0; i<128; i++)
	{
		if (islower(i))
			printf("%d %c\t", i, i);
	}
	return 0;
}
