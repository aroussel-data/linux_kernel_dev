#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{
	int fd, j;
	char *devname = "/dev/mycdrv";

	if (argc > 1)
		devname = argv[1];
	fd = open(devname, O_RDWR);
	for (j = 100; j < 110; j++)
		printf("ioctl(%d) = %d\n", j, ioctl(fd, j, NULL));
	exit(EXIT_SUCCESS);
}
