#include <stdio.h>
#include <string.h>
#define MAX_TEXT 256
int main(void)
{
	char input[MAX_TEXT] = { 0 };
	char output[MAX_TEXT] = { 0 };
	printf("아무 문자열이나 입력하세요.\n입력: ");
	fgets(input, MAX_TEXT - 1, stdin);
	input[strlen(input) - 1] = '\0';
	printf("\n");
	strncpy(output, input, MAX_TEXT);
	strset(output, '*');
	printf("strset: %s\n", output);
	strncpy(output, input, MAX_TEXT);
	strlwr(output);
	printf("strlwr: %s\n", output);
	strncpy(output, input, MAX_TEXT);
	strupr(output);
	printf("strupr: %s\n", output);
	strncpy(output, input, MAX_TEXT);
	strrev(output);
	printf("strrev: %s\n", output);
	return 0;
}
