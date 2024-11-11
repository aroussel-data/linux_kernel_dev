#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/oom.h>
#include <linux/version.h>

static int __init my_init(void)
{
	struct task_struct *p, *t;

	for_each_process_thread(p, t) {
		pr_info("Process ID is %d\n", p->tgid);
		pr_info("Task group (process) ID is %d, task state is %d\n", t->tgid, t->__state);
	}

	/*for_each_process(p) {*/
	/*	pr_info("Process ID is %d, commandline is %s, state is 0x%08x\n", p->tgid, p->comm, p->state);*/
	/*}*/
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