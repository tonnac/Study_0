#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int count, arr1[20], arr2[20];
	FILE * fp;
	for (count = 0;count < 20;count++)
	{
		arr1[count] = 2 * count;
	}
	if ((fp = fopen("direct.txt", "wb")) == NULL)
	{
		fprintf(stderr, "Error opening file");
		exit(1);
	}
	if ((fwrite(arr1, sizeof(int), 20, fp) != 20))
	{
		fprintf(stderr, "Error writing to file");
		exit(1);
	}
	fclose(fp);
	if ((fp = fopen("direct.txt", "rb")) == NULL)
	{
		fprintf(stderr, "Error opening file");
		exit(1);
	}
	if ((fread(arr2, sizeof(int), 20, fp) != 20))
	{
		fprintf(stderr, "Error reading file");
		exit(1);
	}
	fclose(fp);
	for (count = 0;count < 20;count++)
	{
		printf("%d\t%d\n", arr1[count], arr2[count]);
	}
}