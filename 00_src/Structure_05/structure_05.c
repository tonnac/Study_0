#include <stdio.h>

struct drink {
	int milk;
	int beer;
	int whiskey;
	int cola;
	int julice;
};

struct drink input();

main()
{
	struct drink man;
	struct drink women;
	struct drink etc;
	man.beer = 100;
	man.whiskey = 200;
	women.milk = 20;
	women.cola = 20;
	women.julice = 30;
	printf("man beer = %d\twhiskey=%d\n", man.beer, man.whiskey);
	printf("women milk=%d\n", women.milk);
	etc = input();
	printf("etc milk=%d\n", etc.milk);

	return 0;
}

struct drink input()
{
	struct drink ok;
	ok.milk = 100;
	ok.cola = 200;
	ok.beer = 300;
	return ok;
}