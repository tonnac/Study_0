#include <stdio.h>
#include <string.h>

int Strcmp(char*ch1, char*ch2)
{
	int iCh1 = 0;
	int iCh2 = 0;
	while (ch1[iCh1++] != '\0');
	while (ch2[iCh2++] != '\0');
	iCh1--; iCh2--;
	if (iCh1 != iCh2)
	{
		if (iCh1 > iCh2)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		for (int i = 0;i < iCh1;i++)
		{
			if (ch1[i] != ch2[i])
			{
				if (ch1[i] > ch2[i])
				{
					return -1;
				}
				else
				{
					return 1;
				}
			}
		}
		return 0;
	}
}

int Strncmp(char*ch1, char*ch2, int n)
{
	for (int i = 0;i < n;i++)
	{
		if (ch1[i] != ch2[i])
		{
			if (ch1[i] > ch2[i])
			{
				return -1;
			}
			else
			{
				return 1;
			}
		}
	}
	return 0;
}

int main(void)
{
	char ch1[] = "qwjenqw";
	char ch2[] = "qwjenqZ";

	printf("%d\n", Strcmp(ch1, ch2));
	printf("%d\n", Strncmp(ch1, ch2,4));
	return 0;
}