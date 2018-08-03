#include <stdio.h>

int main(void)
{
	char lname[81], fname[81];
	int count, id_num;
	puts("Enter last name, first name, ID number.");
	puts("separated by spaces, then press Enter.");
	count = scanf("%s %s %d", lname, fname, &id_num);
	printf("%d\n", count);
	return 0;
}