#include <stdio.h>

int main(void)
{
	char input[81], *ptr;
	puts("Enter a line, then press Enter");
	puts("Enter a blank line when done.");
	while ((*(ptr = gets(input))) != NULL)
	{
		printf("You Entered %s\n", input);
	}

	return 0;
}