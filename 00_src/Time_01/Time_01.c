#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <time.h>


int main()
{
	time_t now = time(NULL);
	struct tm * lt = localtime(&now);
	printf("������ %d�� %d�� %d���Դϴ�.\n",
		lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday);
	printf("����ð��� %d�� %d���Դϴ�.\n",
		lt->tm_hour, lt->tm_min);

	return 0;
}