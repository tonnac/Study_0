#include <stdio.h>
main()
{
	int a = 5, b = 6, c = 5, d = 1;
	int x;
	x = a<b || a<c && c <d;
	printf("x is : %d", x);
	x = (a<b || a<c) && c <d;
	printf("\nx is : %d", x);
}
