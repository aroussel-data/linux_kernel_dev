#include <linux/module.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static void test_function(void)
{
	pr_info("Inside thread function!\n");
}

static int __init my_init(void)
{
	struct task_struct kthread_create(&test_function, NULL, []);
	// create kernel thread on each cpu with for_each_online_cpu
	// put it to sleep
	pr_info("cpuvar is %d\n", my_cpuvar);
	return 0;
}

static void __exit my_exit(void)
{
	// wake up thread
	// kill thread
	pr_info("Module unloaded\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ALEX");
MODULE_LICENSE("GPL v2");
