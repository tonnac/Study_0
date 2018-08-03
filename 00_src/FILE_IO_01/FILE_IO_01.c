#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	FILE * fp = 0;
	char ch;
	char filename[40];
	char mode[4];
	printf("Enter file name: ");
	gets(filename);
	printf("Enter a mode: ");
	gets(mode);
	fp = fopen(filename, mode);
	if (fp != NULL)
	{
		printf("\nSuccessful opening %s in mode %s.\n", filename, mode);
		fclose(fp);
	}
	else
	{
		printf("\nError opening %s in mode %s.\n", filename, mode);
	}
	return 0;
}