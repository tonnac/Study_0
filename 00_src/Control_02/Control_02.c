#include <stdio.h>
int get_menu_choice(void);
int main(void)
{
	int choice;
	choice = get_menu_choice();
	printf("You choose Menu Option %d\n", choice);
	return 0;
}

int get_menu_choice(void)
{
	int selection = 0;
	do
	{
		printf("1.Add a Record\n");
		printf("2.Change a record\n");
		printf("3.Quit\n");
		printf("1.Enter Selection : ");
		scanf("%d", &selection);
	} while (selection < 1 || selection>3);
	return selection;
}