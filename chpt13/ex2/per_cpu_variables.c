#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/oom.h>
#include <linux/version.h>
#include <linux/percpu.h>

DEFINE_PER_CPU(int, my_cpuvar);

static int __init my_init(void)
{
	pr_info("cpuvar is %d\n", my_cpuvar);
	get_cpu_var(my_cpuvar)++;
	put_cpu_var(my_cpuvar);
	pr_info("cpuvar is %d\n", my_cpuvar);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module unloaded\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ALEX");
MODULE_LICENSE("GPL v2");
