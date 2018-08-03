#include <stdio.h>

int main(void)
{
	char letters[5];
	int i;
	for (i = 0; i < 5;i++)
	{
		letters[i] = getchar();
	}
	for (i = 4;i >= 0;i--)
	{
		putchar(letters[i]);
	}

	return 0;
}