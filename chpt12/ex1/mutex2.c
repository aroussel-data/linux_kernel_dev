#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>

DEFINE_MUTEX(foo);
EXPORT_SYMBOL(foo);

static int __init my_init(void)
{
	pr_info("Checking if mutex locked\n");
	if (mutex_is_locked(&foo) == 1){
		pr_info("Mutex locked\n");
	} else {
		pr_info("Mutex unlocked\n");
		pr_info("Attempting lock\n");
		mutex_lock(&foo);
	}
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
