#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* Strtok(char*ch, char*src)
{
	static int b = 0;
	static char * sarr[10] = { 0, };
	char * sv;
	if (!b || ch != NULL)
	{
		b = 0;
		int a = 0;
		int iCount = 0;
		int iCnt = 0;
		while (ch[iCount++] != 0);		//strlen(ch)
		while (src[iCnt++] != 0);		//strlen(src)
		iCount--; iCnt--;
		sarr[a++] = ch;
		for (int i = 0;i < iCount; i++)
		{
			for (int j = 0;j < iCnt;j++)
			{
				if (ch[i] == src[j])
				{
					ch[i] = 0;
				}
			}
		}
		for (int i = 0;i < iCount - 1; i++)
		{
			if (ch[i] == 0 && ch[i + 1] != 0)
			{
				sarr[a++] = &ch[i + 1];
			}
		}
	}
	sv = sarr[b++];
	return sv;
}

int main(void)
{
	char ch[30] = "jq - wej, wew . qjwen qw";
	char tok[] = " ,.-";
	char ch1[20] = "tekw-, ewq,wl oe-q";

	char * pch = Strtok(ch1, tok);

	while (pch != NULL)
	{
		printf("%s\n", pch);
		pch = Strtok(NULL, tok);
	}

	return 0;
}