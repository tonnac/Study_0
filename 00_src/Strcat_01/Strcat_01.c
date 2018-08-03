#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Strcat(char*des, char*source)
{
	int iCnt = 0;
	int iCount = 0;
	while (des[iCnt++] != '\0');
	while (source[iCount++] != '\0');
	for (int i = 0; i < iCount;i++)
	{
		des[iCnt - 1 + i] = source[i];
	}	
}

char* Strcat1(char*des,char*src)
{
	char * ch = 0;
	int iCnt = 0;
	int iCount = 0;
	while (des[iCnt++] != 0);
	while (src[iCount++] != 0);
	iCnt--;
	ch = (char*)malloc(sizeof(char)*((iCnt)+(iCount)));
	strcpy(ch, des);
	ch += iCnt;
	strcpy(ch, src);
	ch -= iCnt;

	return ch;
}


int main(void)
{
	char des[30] = "kqweqZ";
	char source[30] = "asjkdnaskjd";
	char * new1;
	new1 = Strcat1(des, source);
	printf("%s\n", new1);

	free(new1);
	return 0;
}
