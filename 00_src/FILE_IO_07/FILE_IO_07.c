#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int count, sum, total, status;
	FILE * datafile;
	char c;
	datafile = fopen("values.dat", "r");
	if (datafile == NULL)
	{
		printf("ERROR opening file.");
		exit(0);
	}
	total = 0;
	count = 0;
	do
	{
		status = fscanf(datafile, "%d", &sum);
		if (status == 1)
		{
			total = total + sum;
			count = count + 1;
		}
		else if (status == 0)
		{
			printf("ERROR reading value %d", count);
			exit(0);
		}
	} while (status != EOF);
	printf("Average of values is %d", total / count);
}