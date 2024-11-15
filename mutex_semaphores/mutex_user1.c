#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/atomic.h>
#include <linux/errno.h>

extern struct mutex my_mutex;

static int __init my_init(void)
{
	pr_info("Trying to load module %s\n", KBUILD_MODNAME);
#if 0
	/* this branch should hang if not available */
	if (mutex_lock_interruptible(&my_mutex)) {
		pr_info("mutex unlocked by signal in %s\n", KBUILD_MODNAME);
		return -EBUSY;
	}
#else
	/* this branch will return with failure if not available */
	if (!mutex_trylock(&my_mutex)) {
		pr_info("mutex_trylock failed in %s\n", KBUILD_MODNAME);
		return -EBUSY;
	}
#endif
	pr_info("\n%s mutex grabbed mutex\n", KBUILD_MODNAME);

	return 0;
}

static void __exit my_exit(void)
{
	mutex_unlock(&my_mutex);
	pr_info("\nUnlocking and Exiting from %s\n", KBUILD_MODNAME);
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ALEX");
MODULE_LICENSE("GPL v2");
