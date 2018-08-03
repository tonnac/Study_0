#include <stdio.h>

void call_ref(int*x, int*y);

int main(void)
{
	int a, b;
	int *p, *q;

	a = 1;b = 3;
	p = &a, q = &b;
	printf("\n *p=%d,*q=%d\n", *p, *q);

	call_ref(p, q);
	printf("\n*p=%d,*q=%d\n", *p, *q);

	return 0;
}

void call_ref(int*x, int*y)
{
	*x = 3;
	*y = 5;
}