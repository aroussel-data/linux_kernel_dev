#include <linux/module.h>
#include <linux/init.h>

DEFINE_MUTEX(my_mutex);
EXPORT_SYMBOL(my_mutex);

static int __init my_init(void)
{
	pr_info("\nInit mutex in unlocked state in %s\n", KBUILD_MODNAME);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("\nExiting from %s\n", KBUILD_MODNAME);
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ALEX");
MODULE_LICENSE("GPL v2");
