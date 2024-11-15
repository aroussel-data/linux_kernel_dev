/*Dummy program to be scanned by sparse for errors*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/uaccess.h>

static void my_fun(char *buf1, char *buf2, int count, struct task_struct *s)
{
	int rc;

	rc = copy_from_user(buf2, buf1, count);
}

static int __init my_init(void)
{
	int count = 32;
	char buf1[32], buf2[32];

	my_fun(buf1, buf2, count, 0);
	return 0;
}

static void __exit my_exit(void)
{
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Alex");
