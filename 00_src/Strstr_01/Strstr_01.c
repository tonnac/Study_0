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
	printf("%s로 시작하는 s1의 \n나머지 문자열 : %s\n", s2, ptr);
	ptr = strpbrk(s1, s2);
	printf("첫 문자가 일치하는 s1의 \n나머지 문자열 : %s\n", ptr);



	return 0;
}