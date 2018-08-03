#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct example {
	char*p1;
	char*p2;
	char*p3;
}s={"AA","BBB"};

int main(void)
{
	struct example * p;
	p = &s;
	s.p3 = (char*)malloc(sizeof(char)*3);
	strcpy(s.p3, s.p1);
	printf("%s %s %s\n", s.p1, s.p2, s.p3);
	printf("%s %s %s\n",p->p1, p->p2, p->p3);
	printf("%s %s %s\n\n", (*p).p1, (*p).p2, (*p).p3);


	free(p->p3);
	return 0;
}