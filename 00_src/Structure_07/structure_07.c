#include <stdio.h>

int main()
{
	struct S {
		char c1;
		char c2;
	};

	struct S a;
	printf("sizeof(S) = %d\n", sizeof(a));

	return 0;
}