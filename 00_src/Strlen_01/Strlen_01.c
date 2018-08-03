#include <stdio.h>
#include <string.h>

int main(void)
{
	size_t length;
	char buf[80];
	while (1)
	{
		puts("Enter a line of text.");
		puts("blank line terminates");
		gets(buf);
		length = strlen(buf);
		if (length != 0)
			printf("%u characters.\n\n", length);
		else
			break;
	}
}