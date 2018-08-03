#include <stdio.h>
#include <fcntl.h>

int main(int argc, char*argv[])
{
	int fd1, fd2;
	char buf[BUFSIZ];
	int n;
	if (argc != 3)
	{
		fprintf(stderr, "USAGE:%s sourcefile objectfile\n", *argv);
		return(1);
	}
	if ((fd1 = open(*(argv + 1), O_RDONLY | O_BINARY)) < 0)
	{
		fprintf(stderr, "ERROR : Cannot open %s \n", *(argv + 1));
		return (2);
	}
	if ((fd2 = open(*(argv + 2), O_WRONLY | O_TRUNC | O_CREAT | O_BINARY, 0700)) < 0)
	{
		fprintf(stderr, "ERROR : Cannot create %s\n", *(argv + 2));
		return (3);
	}
	printf("FileCopy %s to %s\n\n", *(argv + 1), *(argv + 2));
	while ((n = read(fd1, buf, BUFSIZ)) > 0)
	{
		if (write(fd2, buf, n) != n)
		{
			fprintf(stderr, "ERROR in writing %s\n", *(argv + 2));
			return (4);
		}
		if (n < 0)
		{
			fprintf(stderr, "ERROR in reading %s\n", *(argv + 1));
			close(fd1);
			close(fd2);
		}
	}
}