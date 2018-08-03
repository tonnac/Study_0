#include <stdio.h>

int main(void)
{
	int i, integer[2];
	char ch[2];
	integer[0] = 1; integer[1] = 2;
	ch[0] = 'a'; ch[1] = 'b';
	for (i = 0;i < 2;i++)
		printf("\n%d", integer[i]);
	for (i = 0;i < 2;i++)
		printf("\n%c", ch[i]);
	return 0;
}