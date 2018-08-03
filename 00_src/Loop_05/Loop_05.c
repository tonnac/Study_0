#include <stdio.h>
#include <conio.h>

int main(void)
{
	int yn;
	do
	{
		printf("Continue(Y/N)?");
		yn = getche();
		putchar('\n');
	} while (yn != 'Y' && yn != 'N');
	return 0;
}