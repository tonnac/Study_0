#include <stdio.h>
#include <string.h>
#define MAX_INPUT 256
int main(void)
{
	char input[MAX_INPUT] = { 0 };
	char *ptr = NULL;
	int count = 0;
	printf("�ƹ� ���ڿ��̳� �Է��ϼ���. a�� ã�Ƶ帮�ڽ��ϴ�.\n�Է�: ");
	fgets(input, MAX_INPUT - 1, stdin);
	printf("\n");
	ptr = input;
	while (1)
	{
		ptr = strchr(ptr, 'a');
		if (ptr == NULL)
			break;
		printf("%d��° ���ڴ� a�Դϴ�.\n", ptr - input + 1);
		count++;
		ptr++;
	}
	printf("a�� �� %d�� ���Խ��ϴ�.\n", count);
	return 0;
}
