#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void clear_kb(void);
int main(void)
{
	FILE * fp;
	int data[5] = { 111,222,333,444,555 };
	int count;
	char filename[20];
	clear_kb();
	printf("Enter a filename: ");
	gets(filename);

	fp = fopen(filename, "wt");

	if (fp == NULL)
	{
		fprintf(stderr, "Error opening file");
		exit(1);
	}
	for (count = 0;count < 5;count++)
	{
		fprintf(fp, "\ndata[%d] = %d", count, data[count]);
	}
	fclose(fp);
	return 0;
}

void clear_kb(void)
{
	char junk[80];
	gets(junk);
}