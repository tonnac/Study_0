#include <stdio.h>
#include <string.h>
#define MAX_INPUT 256
int main(void)
{
	char input[MAX_INPUT] = { 0 };
	char *ptr = NULL;
	int count = 0;
	printf("아무 문자열이나 입력하세요. a를 찾아드리겠습니다.\n입력: ");
	fgets(input, MAX_INPUT - 1, stdin);
	printf("\n");
	ptr = input;
	while (1)
	{
		ptr = strchr(ptr, 'a');
		if (ptr == NULL)
			break;
		printf("%d번째 글자는 a입니다.\n", ptr - input + 1);
		count++;
		ptr++;
	}
	printf("a가 총 %d번 나왔습니다.\n", count);
	return 0;
}
