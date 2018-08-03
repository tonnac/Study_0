#include <stdio.h>
#include <time.h>
#include <memory.h>

int main(void)
{
	struct tm * today, theday;
	time_t now = time(NULL);
	today = localtime(&now);
	memcpy(&theday, today, sizeof(theday));
	theday.tm_mday += 20;
	mktime(&theday);

	printf("오늘은 %d년 %d월 %d일입니다.\n"
		, today->tm_year + 1900, today->tm_mon + 1, today->tm_mday);
	printf("20일 후에는 %d년 %d월 %d일이 됩니다.\n",
		theday.tm_year + 1900, theday.tm_mon + 1, theday.tm_mday);
	return 0;
}