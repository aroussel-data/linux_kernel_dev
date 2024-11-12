#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>

extern struct mutex foo;

static int __init my_init(void)
{

	pr_info("Module loaded\n");
	pr_info("Locking mutex\n");

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
