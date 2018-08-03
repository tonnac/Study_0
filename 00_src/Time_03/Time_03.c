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

	printf("������ %d�� %d�� %d���Դϴ�.\n"
		, today->tm_year + 1900, today->tm_mon + 1, today->tm_mday);
	printf("20�� �Ŀ��� %d�� %d�� %d���� �˴ϴ�.\n",
		theday.tm_year + 1900, theday.tm_mon + 1, theday.tm_mday);
	return 0;
}