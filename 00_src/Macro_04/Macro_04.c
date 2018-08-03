#include <stdio.h>

#define PRI(x) printf(#x"=%d\n",x);
#define CON(x,y) x ## y

int main(void)
{
#define TEST 100
#ifdef TEST
	printf("TEST is defined.\n");
#endif
#ifdef SIZE
	printf("SIZE is defined.\n");
#endif
#ifndef TEST
	printf("TEST is not defined.\n");
#endif
#ifndef SIZE
	printf("SIZE is not defined.\n");
#endif
#undef TEST
#define SIZE
#ifdef TEST
	printf("TEST is defined.\n");
#endif
#ifdef SIZE
	printf("SIZE is defined.\n");
#endif
#ifndef TEST
	printf("TEST is not defined.\n");
#endif
#ifndef SIZE
	printf("SIZE is not defined.\n");
#endif
	PRI(10);
	printf("%s\n",CON("qwe", "eee"));
	return 0;
}