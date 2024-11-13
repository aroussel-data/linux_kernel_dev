#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>

DEFINE_MUTEX(foo);
EXPORT_SYMBOL(foo);

static int __init my_init(void)
{
	pr_info("Checking if mutex locked\n");
	if (!mutex_trylock(&foo)){
		pr_info("Failed getting lock in: %s\n", KBUILD_MODNAME);
		return -EPERM;
	};
	pr_info("Mutex locked? %d\n", mutex_is_locked(&foo));
	return 0;
}

static void __exit my_exit(void)
{
	mutex_unlock(&foo);
	pr_info("Module unloaded\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ALEX");
MODULE_LICENSE("GPL v2");
