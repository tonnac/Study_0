#include <stdio.h>

#define MAX_INPUT 128


int main(void)
{
	char text[MAX_INPUT];
	int total;
	double average;
	FILE * fp;
	if ((fp = fopen("score.txt", "rt")) == NULL)
	{
		printf("파일을 열지 못했습니다.\n");
		return 1;
	}
	fread(text, 14, 1, fp);
	printf("%s\n", text);
	fread(text, 7, 1, fp);
	fread(&total, sizeof(int), 1, fp);
	printf("%s%d\n", text, total);
	fread(text, 7, 1, fp);
	fread(&average, sizeof(double), 1, fp);
	printf("%s%f\n", text, average);
	fclose(fp);
	return 0;
}