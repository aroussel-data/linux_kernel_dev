#include <linux/module.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static struct task_struct *tsk[NR_CPUS];

static void print_cpu(char *s)
{
	preempt_disable();
	pr_info("%s cpu=%d.\n", s, smp_processor_id());
	preempt_enable();
}

static int thr_fun(void *thr_arg)
{
	do {
		print_cpu("SLEEP in Thread Function ");
		msleep_interruptible(2000);
		print_cpu("msleep over in Thread Function");
	} while (!kthread_should_stop());
	return 0;
}

static int __init my_init(void)
{
	int i;

	print_cpu("Loading module");
	for_each_online_cpu(i) {
		tsk[i] = kthread_create(thr_fun, NULL, "thr_fun/%d", i);
		if (!tsk[i]) {
			pr_info("Failed to generate a kernel thread\n");
			return -1;
		}
		kthread_bind(tsk[i], i);
		pr_info("About to wake up and run the thread for cpu=%d\n", i);
		wake_up_process(tsk[i]);
		pr_info("Staring thread for cpu %d", i);
		print_cpu("on");
	}
	return 0;
}

static void __exit my_exit(void)
{
	int i;

	for_each_online_cpu(i) {
		pr_info(" Kill Thread %d", i);
		kthread_stop(tsk[i]);
		print_cpu("Kill was done on ");
	}
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ALEX");
MODULE_LICENSE("GPL v2");
