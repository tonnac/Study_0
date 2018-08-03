#include <stdio.h>
#include <string.h>

char* Strset(char*ch, int a)
{
	int iCnt = 0;
	while (ch[iCnt++] != 0);
	iCnt--;
	for (int i = 0;i < iCnt;i++)
	{
		ch[i] = a;
	}
	return ch;
}

char* Strnset(char*ch, int a, size_t n)
{
	for (int i = 0;i < n;i++)
	{
		ch[i] = a;
	}
	return ch;
}

int main(void)
{
	char ch[] = "abcdefghijklmnopqrstuvwxyz";

	printf("%s\n", Strnset(ch, 'd',5));
	return 0;
}