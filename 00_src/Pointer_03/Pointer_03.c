#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int p, q;
	p = 3;
	q = 2;
	printf("\n*p==%d,*q==%d\n", p, q);
	printf("\n*p==%p,*q==%p\n", p, q);
	printf("\n*p==%p,*q==%p\n", &p, &q);

	return 0;
}