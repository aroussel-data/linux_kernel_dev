#include <linux/module.h>
#include <linux/init.h>
#include <linux/utsname.h>

static int __init my_init(void)
{
	struct new_utsname *utsname = init_utsname();

	pr_info("sysname    = %s\n"
		"nodename   = %s\n"
		"release    = %s\n"
		"version    = %s\n"
		"machine    = %s\n"
		"domainname = %s\n",
		utsname->sysname, utsname->nodename, utsname->release,
		utsname->version, utsname->machine, utsname->domainname);

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
