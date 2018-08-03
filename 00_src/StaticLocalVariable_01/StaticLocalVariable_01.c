#include <stdio.h>
void func()
{
	static int a = 0;
	a = a + 1;
	printf("%d\n", a);
}

int main(void)
{
	func();
	func();
	func();
	return 0;
}