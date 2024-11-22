/*Rather than changing the nice values by using the nice utility, let's try using the set|get_priority() syscalls.*/
/*In theory only root can actually set the priority of a process, otherwise we can only get_priority.*/
/*Unless running the program as sudo, we wont be able to setpriority to a higher nice value than*/
/*the default of 1 that the program is running in. However we can lower the priority down to 19*/
/*without being root*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int process_id;
	if (argc > 1) {
		process_id = atoi(argv[1]);
	} else {
		process_id = getpid();
	}
	int priority_value = getpriority(PRIO_PROCESS, process_id);
	int new_priority_value = setpriority(PRIO_PROCESS, process_id, -20);
	priority_value = getpriority(PRIO_PROCESS, process_id);
	printf("\nProcess id = %d\n", process_id);
	printf("\nPriority val = %d\n", priority_value);
}
