#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX_INPUT 20
int main(void)
{
	int noon;				// 오전오후 저장
	time_t now;				// 현재시각 저장
	struct tm *lt = NULL;			// 현재시각 저장
	char name[MAX_INPUT] = { 0 };		// 이름 저장
	char output[100] = { 0 };			// 출력 문장 저장
	char *greeting[] = { "좋은 아침입니다. ", "활기찬 오후 되세요. " };
	char *postfix[] = { "님", "씨" };
	printf("이름을 입력하세요: ");
	fgets(name, MAX_INPUT - 1, stdin);		// 이름을 입력 받음
	name[strlen(name) - 1] = '\0';		// '\n' 제거
	now = time(NULL);			// 현재 시각을 얻음
	lt = localtime(&now);
	if (lt->tm_hour < 12) noon = 0;		// 정오를 넘지 않았으면 0
	else	noon = 1;				// 정오를 넘었으면 1

	strcpy(output, greeting[noon]);		// 인사말 복사
	strcat(output, name);			// 이름 붙이기
	strcat(output, postfix[noon]);		// 존칭 붙이기
	printf("%s\n", output);
	return 0;
}
