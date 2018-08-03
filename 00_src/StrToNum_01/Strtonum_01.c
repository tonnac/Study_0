#include <stdio.h>
#include <string.h>

int Atoi(char *ch)		//48 57
{
	int i;
	int re = 0;
	int Len = 0;
	int iCount = 0;
	while (ch[iCount++] != 0);
	iCount--;
	for (i = 0;i < iCount;i++)
	{
		if (ch[i] >= '0' && ch[i] <= '9')
		{
			continue;
		}
		else
		{
			break;
		}
	}
	Len = i - 1;
	for (int i = 0;i <= Len;i++)
	{
		re += (ch[i] - 48)*exp(Len - i);
	}
	return re;
}

int exp(int n)
{
	int total = 1;
	if (n == 0)
	{
		return total;
	}
	else
	{
		for (int i = 0;i < n;i++)
		{
			total *= 10;
		}
		return total;
	}
}

int main(void)
{
	char ch1[] = "1234ds56";
	printf("%d\n", Atoi(ch1));
	return 0;
}