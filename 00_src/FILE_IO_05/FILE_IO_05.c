#include <stdio.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
	int fd;
	long int size;
	int n;
	char buf[BUFSIZ];
	if (argc == 1) {
		fprintf(stderr, "USAGE:%sfile(1)file(2)...file(n)\n", *argv);
		return (0);
	}
	while (--argc > 0)
	{
		if ((fd = open(*++argv, O_RDONLY | O_BINARY)) == -1)
		{
			fprintf(stderr, "ERROR: Cannot open %s\n", *argv);
			continue;
		}
		size = 0;
		while ((n = read(fd, buf, BUFSIZ)) > 0)
			size += n;
		if (n == 0)
			fprintf(stdout, "%s:%ld bytes.\n", *argv, size);
		else
			fprintf(stderr, "ERROR in reading %s\n", *argv);
	}
	close(fd);
	return 0;
}