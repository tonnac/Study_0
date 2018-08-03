#include <stdio.h>

int main(void)
{
	int a = 4;
	switch (a)
	{
	case 1:
		printf("One\n");break;
	case 2:
		printf("Two\n");break;
	case 3:
		printf("Three\n");break;
	default:
		printf("Another value\n");
	}
}