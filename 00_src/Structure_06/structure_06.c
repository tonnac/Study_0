#include <stdio.h>
struct da {
	int x, y, z;
};

int total(struct da tot)
{
	return (tot.x + tot.y + tot.z);
}

int main(void)
{
	struct da val = { 10,30,50 };
	int sum = 0;
	sum = total(val);
	printf("Sum = %d\n", sum);

	return 0;
}