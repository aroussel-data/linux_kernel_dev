#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>

#define __NR_my_syscall 463
#define my_syscall(a) syscall(__NR_my_syscall, a)

int main(int argc, char *argv[])
{
	unsigned long p1 = 1;
	long rc;

	printf("\nDoing my_syscall1, p1 = %ld\n", p1);
	rc = my_syscall(p1);
	/*printf("\nErrno = %d\n", errno);*/
	printf("\nReturned my_syscall, p1 = %ld, rc = %ld\n", p1, rc);

	exit(EXIT_SUCCESS);
}
