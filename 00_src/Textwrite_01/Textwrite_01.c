#include <stdio.h>

int main(void)
{
	int students, s, sum = 0;
	int score[] = { 89,90,95,70,82,60,92,88 };
	double average;
	FILE * fp;
	students = sizeof(score) / sizeof(int);
	for (s = 0; s < students;s++)
	{
		sum += score[s];
	}
	average = (double)sum / students;

	if ((fp = fopen("score.txt", "wt")) == NULL)
	{
		printf("파일을 열지 못했습니다.\n");
		return 1;
	}
	fputs("성적처리 결과\n", fp);
	fprintf(fp, "총점:%d\n", sum);
	fprintf(fp, "평균:%0.2f\n", average);
	fclose(fp);
	return 0;
}