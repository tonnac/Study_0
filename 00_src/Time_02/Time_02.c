#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t now = time(NULL);
	time_t worldcup;
	struct tm worldcupDay = { 0,0,0,1,5,110,0,0,0 };
	double diff;
	worldcup = mktime(&worldcupDay);
	diff = difftime(worldcup, now);
	printf("%d일 남았습니다.\n",
		(int)diff / 60 / 60 / 24);
	return 0;
}