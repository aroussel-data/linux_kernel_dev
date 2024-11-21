/*Rather than changing the nice values by using the nice utility, let's try using the set|get_priority() syscalls.*/
/*In theory only root can actually set the priority of a process, otherwise we can only get_priority.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int process_id = getpid();
	printf("\ncurrent pid = %d\n", process_id);
}
