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
	fgets(text, MAX_INPUT, fp);
	printf("%s", text);
	fscanf(fp, "%s", text);
	printf("%s\n", text);
	fscanf(fp, "%s", text);
	printf("%s\n", text);
	fclose(fp);
	return 0;
}