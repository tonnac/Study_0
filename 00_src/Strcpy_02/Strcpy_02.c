#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX_INPUT 20
int main(void)
{
	int noon;				// �������� ����
	time_t now;				// ����ð� ����
	struct tm *lt = NULL;			// ����ð� ����
	char name[MAX_INPUT] = { 0 };		// �̸� ����
	char output[100] = { 0 };			// ��� ���� ����
	char *greeting[] = { "���� ��ħ�Դϴ�. ", "Ȱ���� ���� �Ǽ���. " };
	char *postfix[] = { "��", "��" };
	printf("�̸��� �Է��ϼ���: ");
	fgets(name, MAX_INPUT - 1, stdin);		// �̸��� �Է� ����
	name[strlen(name) - 1] = '\0';		// '\n' ����
	now = time(NULL);			// ���� �ð��� ����
	lt = localtime(&now);
	if (lt->tm_hour < 12) noon = 0;		// ������ ���� �ʾ����� 0
	else	noon = 1;				// ������ �Ѿ����� 1

	strcpy(output, greeting[noon]);		// �λ縻 ����
	strcat(output, name);			// �̸� ���̱�
	strcat(output, postfix[noon]);		// ��Ī ���̱�
	printf("%s\n", output);
	return 0;
}
