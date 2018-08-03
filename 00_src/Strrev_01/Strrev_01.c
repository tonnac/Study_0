#include <stdio.h>
#include <string.h>

void Strrev(char*ch)
{
	int iCnt = 0;
	char temp;
	while (ch[iCnt++] != 0);
	iCnt -= 2;
	for (int i = 0;i < iCnt / 2;i++)
	{
		temp = ch[i];
		ch[i] = ch[iCnt - i];
		ch[iCnt - i] = temp;
	}
}

int main(void)
{
	char ch[] = "abcdefghijklmn";

	Strrev(ch);

	printf("%s\n", ch);

	return 0;
}