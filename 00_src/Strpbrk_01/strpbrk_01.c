#include <stdio.h>
#include <string.h>

char* Strpbrk(char*ch, char*sr)
{
	char * re;
	int iCnt = 0;
	int iCount = 0;
	while (ch[iCnt++] != '\0');
	while (sr[iCount++] != '\0');
	iCnt--; iCount--;
	for (int i = 0;i < iCnt;i++)
	{
		for (int j = 0;j < iCount;j++)
		{
			if (ch[i] == sr[j])
			{
				re = &ch[i];
				return re;
			}
		}
	}
	return NULL;
}

int main(void)
{
	char ch[30] = "qopiuwe";

	printf("%s\n",Strpbrk(ch, "weip"));

	return 0;
}