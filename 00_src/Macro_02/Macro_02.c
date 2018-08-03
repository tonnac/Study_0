#include <stdio.h>

void swap(int*a, int*b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

#define swap(a,b) {a^=b;b^=a;a^=b;}