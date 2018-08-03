#include <stdio.h>
#define MAX 4
struct part {
	int num;
	char name[10];
}data[MAX] = { 1,"aaa",2,"bbb",3,"ccc",4,"ddd" };

struct part * p_part;
int count;

int main()
{
	p_part = data;
	for (count = 0;count < MAX;count++)
	{
		printf("At Address %x : %d %s\n", p_part, p_part->num, p_part->name);
		p_part++;
	}

	return 0;
}