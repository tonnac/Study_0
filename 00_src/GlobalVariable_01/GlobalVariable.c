#include <stdio.h>
int a;
void func(void)
{
	a = 5;
}
int main(void)
{
	func();
	printf("%d\n", a);
	a = 10;
	printf("%d\n", a);
	return 0;
}