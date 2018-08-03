#include <stdio.h>
#include <string.h>

char* Strlwr(char *str)
{
	int iCount = 0;
	while (str[iCount++] != 0);
	iCount--;
	for (int i = 0;i < iCount;i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 'a' - 'A';
		}
	}
	return str;
}
char* Strupr(char *str)
{
	int iCount = 0;
	while (str[iCount++] != 0);
	iCount--;
	for (int i = 0;i < iCount;i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] -= 'a' - 'A';
		}
	}
	return str;
}



int main(void)
{
	char ch[] = "ASKDJNASKDJN";

	printf("%s\n", Strlwr(ch));

	return 0;
}