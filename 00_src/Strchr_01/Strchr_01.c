#include <stdio.h>
#include <string.h>

char* Strchr(char*ch, char a)
{
	char * des;
	int iCount = 0;
	while (ch[iCount++] != '\0');
	iCount--;
	for (int i = 0; i < iCount;i++)
	{
		if (ch[i] == a)
		{
			des = &ch[i];
			return des;
		}
	}
	return NULL;
}
char* Strrchr(char*ch, char a)
{
	char * des;
	int iCount = 0;
	while (ch[iCount++] != '\0');
	iCount--;
	for (int i = iCount; i >=0 ;i--)
	{
		if (ch[i] == a)
		{
			des = &ch[i];
			return des;
		}
	}
	return NULL;
}

int main(void)
{
	char ch[30] = "askejnwaeqz";

	printf("%s\n",Strchr(ch, 'e'));
	printf("%s\n", Strrchr(ch, 'e'));
	return 0;
}