#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#define GET_ELAPSED_TIME(tv1, tv2) (\
(double)((tv2.tv_sec - tv1.tv_sec) \
	  + .000001 * (tv2.tv_usec - tv1.tv_usec)))

#define JMAX (400*100000)

/*Do some computation that will take some time so that we can see how the*/
/*scheduler treated the process as a function of its nice value.*/
double do_compute(void)
{
	int j;
	double x = 0.0;
	struct timeval tv1, tv2;

	gettimeofday(&tv1, NULL);
	for (j = 0; j < JMAX; j++)
		x += 1.0 / (exp((1 + x * x) / (2 + x * x)));
	gettimeofday(&tv2, NULL);
	return GET_ELAPSED_TIME(tv1, tv2);
}

/*Pass a nice value to the program and have it change its nice values*/
int main(int argc, char *argv[])
{
	// program will receive a nice value, but default to 0
	int nice_value = 0;
	char fname[256];
	FILE *fp;

	if (argc > 1)
		nice_value = atoi(argv[1]);
	printf("nice val: %d\n", nice_value);

	int process_id = getpid();
	sprintf(fname, "/proc/%d/schedstat", process_id);
	printf("fname: %s\n", fname);

	sleep(3);

	// open the schedstat file to get:
	// time spent scheduled in on CPU and executing in nanosecs I think
	// time spent waiting in runqueue in nanosecs I think
	// num timeslices pid was scheduled for
	fp = fopen(fname, "r");
	if (!fp) {
		printf("failed opening schedstat file\n");
		exit(EXIT_FAILURE);
	}

	// set nice val
	nice(nice_value);
	// a lower nice value should result in getting greater number of timeslices

	int num_timeslices;
	long scheduled_nanosecs, sleep_nanosecs;
	// read values from fd
	fscanf(fp, "%ld %ld %d", &scheduled_nanosecs, &sleep_nanosecs, &num_timeslices);
	fclose(fp);
	// convert to seconds
	double cpu_seconds = (float)scheduled_nanosecs / 1000000000;
	double sleep_seconds = (float)sleep_nanosecs / 1000000000;
	printf("\nticks_cpu=%ld ticks_sleep=%ld nsched=%d t_cpu=%10g t_sleep=%10g\n",
	       scheduled_nanosecs, sleep_nanosecs, num_timeslices, cpu_seconds, sleep_seconds);

	double exec_time = do_compute();
	printf("elapsed_time was: %10g\n", exec_time);
	exit(EXIT_SUCCESS);
}
