#include <stdio.h>
#include <string.h>

char* Strstr(char*ch, char*sr)
{
	int a;
	int iCnt = 0;
	int iCount = 0;
	while (ch[iCnt++] != 0);
	while (sr[iCount++] != 0);
	iCnt--; iCount--;
	for (int i = 0; i < iCnt;i++)
	{
		a = 0;
		if (*(ch + i) == *(sr+0))
		{
			for (int j = 1; j < iCount; j++)
			{
				if (*(ch + i + j) != *(sr + j))
				{
					a++;
					break;
				}
			}
			if(!a)
			{
				return ch+i;
			}
		}
	}
	return NULL;
}


int main(void)
{
	char *s1 = "This is a string";
	char *s2 = "a st";
	char *ptr;
	ptr = Strstr(s1, s2);
	printf("string : %s\n", s1);
	printf("%s�� �����ϴ� s1�� \n������ ���ڿ� : %s\n", s2, ptr);
	ptr = strpbrk(s1, s2);
	printf("ù ���ڰ� ��ġ�ϴ� s1�� \n������ ���ڿ� : %s\n", ptr);



	return 0;
}