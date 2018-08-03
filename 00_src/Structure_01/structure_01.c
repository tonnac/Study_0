#include <stdio.h>
#include <string.h>
#include <conio.h>
struct test
{
	int a;
	char str[20];
	float b;
};

int main(void)
{
	struct test ok; //4-- ??
	ok.a = 10;
	strcpy(ok.str, "TEST OK");
	ok.b = 10.5;
	printf("%d %s %f\n", ok.a, ok.str, ok.b);

	return 0;
}