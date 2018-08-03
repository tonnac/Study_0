#include <stdio.h>

int main(void)
{
	int Var1, Var2;
	int * pVar = &Var1;

	*pVar = 10;
	printf("%d\n", Var1);

	Var2 = *pVar;
	printf("%d\n", Var2);

	pVar = &Var2;
	*pVar = 5;
	printf("%d\n", Var2);

	return 0;
}