#define _CRT_SECURE_NO_WARNINGS

#include <io.h>
#include <stdio.h>
#include <time.h>

int main()
{
	struct _finddata_t file;
	intptr_t hFile = _findfirst("*.*", &file);
	do
	{
		printf("%s\n", file.name);
		time_t create = file.time_create;
		time_t access = file.time_access;
		time_t write = file.time_write;
		struct tm * ltc = localtime(&create);
		struct tm * lta = localtime(&access);
		struct tm * ltw = localtime(&write);
		char buf[256];

		strftime(buf, 256, "%m월 %d일 %H시", ltc);

		printf("%s%s%s\n", ctime(&create), ctime(&access), ctime(&write));
		printf("%s%s%s\n", asctime(ltc), asctime(lta), asctime(ltw));
		//strftime(buf, 256, "%m월 %d일 %H시", ltc);
		//printf("%s\n", buf);
		//strftime(buf, 256, "%m월 %d일 %H시", lta);
		//printf("%s\n", buf);
		//strftime(buf, 256, "%m월 %d일 %H시", ltw);
		//printf("%s\n", buf);
		puts("===============================================================");
	} while (_findnext(hFile, &file)==0);
	return 0;
}