#include <stdio.h>

int main(void)
{
	int var = 1;
	int * ptr;
	ptr = &var;
	printf("Direct,var = %d\n", var);
	printf("Indirect,var=%d\n", *ptr);
	printf("The address of var = %p\n", &var);
	printf("The address of var = %p\n", ptr);
	return 0;
}