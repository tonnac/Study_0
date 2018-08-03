#include <stdio.h>

int main(void)
{
	int i;
	static int integer[5];
	static char ch[5];
	static float f[5];

	for (i = 0;i < 5;i++)
		printf("%3d", integer[i]);
	printf("\n");
	for (i = 0;i < 5;i++)
		printf("%3d", ch[i]);
	printf("\n");
	for (i = 0;i < 5;i++)
		printf("%4.1f", f[i]);
	return 0;
}