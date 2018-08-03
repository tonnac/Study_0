#include <stdio.h>
#include <string.h>

size_t Strcspn(char*ch, char*sr)
{
	int iCount = 0;
	int iCnt = 0;
	while (ch[iCount++] != '\0');
	while (sr[iCnt++] != '\0');
	iCount--; iCnt--;
	for (int i = 0; i < iCount;i++)
	{
		for (int j = 0;j < iCnt;j++)
		{
			if (ch[i] == sr[j])
			{
				return i;
			}
		}
	}
	return iCount;
}
size_t Strspn(char*ch, char*sr)
{
	int iCount = 0;
	int iCnt = 0;
	int a = 0;
	while (ch[iCount++] != '\0');
	while (sr[iCnt++] != '\0');
	iCount--; iCnt--;
	for (int i = 0; i < iCount;i++)
	{
		a = 0;
		for (int j = 0;j < iCnt;j++)
		{
			if (ch[i] == sr[j])
			{
				a++;
				break;
			}
		}
		if (!a)
		{
			return i;
		}
	}
	return iCount;
}



int main(void)
{
	char ch[30] = "qwe asd zxc";
	
	printf("%d\n", Strcspn(ch, "pzoi"));
	printf("%d\n", Strspn(ch, "qwzase "));

	return 0;
}