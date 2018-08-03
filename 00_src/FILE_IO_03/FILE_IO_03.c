#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int  i1, i2, i3, i4, i5;
	FILE * fp;
	if ((fp = fopen("qwer.txt", "r")) == NULL)
	{
		fprintf(stderr, "Error opening file.");
		exit(1);
	}
	fscanf(fp, "%d %d %d %d %d", &i1, &i2, &i3, &i4, &i5);
	printf("%d %d %d %d %d\n", i1, i2, i3, i4, i5);
	fclose(fp);
	return 0;
}