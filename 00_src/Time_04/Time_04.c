#include <stdio.h>
#include <time.h>
#include <memory.h>
#define MAX_OUTPUT 256

int main(void)
{
	time_t now = time(NULL);
	struct tm * lt = localtime(&now);
	char output[MAX_OUTPUT];
	printf("ctime:%s", ctime(&now));
	printf("asctime:%s", asctime(lt));
	strftime(output, MAX_OUTPUT, "%Y³â %m¿ù %dÀÏ %X", lt);
	strftime(output, MAX_OUTPUT, "%I:%M:%S", lt);
	printf("strftime:%s\n", output);

	return 0;
}