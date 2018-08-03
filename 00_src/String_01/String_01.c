#include <stdio.h>

int main(void)
{
	unsigned char x;
	for (x = 65;x <= 90;x++)
	{
		printf("ASCII code %d is Character : %c\n", x, x);
	}

	return 0;
}