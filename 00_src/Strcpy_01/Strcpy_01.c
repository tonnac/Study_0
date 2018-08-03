#include <stdio.h>

void Strcpy(char*source, char*destination)
{
	int i;
	i = 0;
	while ((source[i] = destination[i]) != '\0')
	{
		i++;
	}
}

void Strcpy1(char*s, char*t)
{
	while ((*s = *t) != '\0')
	{
		s++;
		t++;
	}
}

void Strcpy2(char*s, char*t)
{
	while (((*s++) = (*t++)) != '\0');
}


int main(void)
{
	char ch[30];
	char ch1[30];
	char ch2[30];
	char des1[30] = "qwertasdf";
	char des2[30] = "zxcvasdfqwer";
	char des3[30] = "opiyutkljuytyu";

	Strcpy(ch, des1);
	Strcpy1(ch1, des2);
	Strcpy2(ch2, des3);
	printf("%s\n", ch);
	printf("%s\n", ch1);
	printf("%s\n", ch2);

	return 0;
}