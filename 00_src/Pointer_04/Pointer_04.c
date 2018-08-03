#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int*p, *q;
	int a, b;
	a = 1; b = 2;
	p = &a;
	q = &b;
	printf("\n&a==%p,a==%d,&b==%p,b==%d", &a, a, &b, b);
	printf("\np==%p,*p==%d,q==%p,*q==%d\n", p, *p, q, *q);

	return 0;
}