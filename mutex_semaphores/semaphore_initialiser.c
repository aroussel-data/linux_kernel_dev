#include <linux/module.h>
#include <linux/init.h>
#include <linux/atomic.h>
#include <linux/version.h>
#include <linux/semaphore.h>

DEFINE_SEMAPHORE(my_sem, 1);
EXPORT_SYMBOL(my_sem);

static int __init my_init(void)
{
	pr_info("\nInitializing semaphore, ");
	pr_info("semaphore_count=%u\n", my_sem.count);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("\nExiting semaphore, ");
	pr_info("semaphore_count=%u\n", my_sem.count);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Alex");
MODULE_LICENSE("GPL v2");
