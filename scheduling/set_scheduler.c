/*Trying out the same thing with the get|set_scheduler syscalls for changing the scheduling
 * policy and priorities*/

#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

void print_policy(int sched_policy) {
	if (sched_policy == SCHED_OTHER)
		printf("sched_policy = SCHED_OTHER = %d\n", sched_policy);
	if (sched_policy == SCHED_FIFO)
		printf("sched_policy = SCHED_FIFO = %d\n", sched_policy);
	if (sched_policy == SCHED_RR)
		printf("sched_policy = SCHED_RR = %d\n", sched_policy);
}

int main(int argc, char *argv[])
{
	int process_id;
	if (argc > 1) {
		process_id = atoi(argv[1]);
	} else {
		process_id = getpid();
	}
	int sched_policy = sched_getscheduler(process_id);
	print_policy(sched_policy);

	// to set policy we need to use sched_param
	struct sched_param param;
	param.sched_priority = 50;

	// set new policy
	sched_setscheduler(process_id, SCHED_FIFO, &param);

	// change to policy wont be visible unless run as root
	sched_policy = sched_getscheduler(process_id);
	print_policy(sched_policy);
}
