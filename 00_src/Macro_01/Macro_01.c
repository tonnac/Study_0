#include <stdio.h>
#define MAX 100
#define MIN 10
#define FALSE 0
#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))
#define NL '\n'
#define SPACE ' '
#define TAB '\t'
#define TABNO 8
#define PR(x) printf("%d\n",x)
#define PRC(x) printf("%c\n",x)
#define tab(x,n) for(x=0;x<n;x++) putchar(SPACE)

int main(void)
{
	static char ca[] = "this\tis\tstring.\n";
	char * cp = ca;
	int i = MAX;
	int j = MIN;
	if (max(i - j, j) > min(i + j, i))
	{
		++i;
	}
	else
	{
		--j;
	}
	PR(i);
	PR(j);

	while (*cp != FALSE)
	{
		if (*cp == TAB)
		{
			tab(i, TABNO);
		}
		else if (*cp == NL)
		{
			break;
		}
		else
		{
			PRC(*cp);
		}
		++cp;
	}
}