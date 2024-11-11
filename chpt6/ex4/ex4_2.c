#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void)
{
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module unloaded\n");
}

int foo = 123;
EXPORT_SYMBOL(foo);

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ALEX");
MODULE_LICENSE("GPL v2");
