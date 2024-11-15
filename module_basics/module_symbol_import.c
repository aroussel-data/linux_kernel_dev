#include <linux/module.h>
#include <linux/init.h>

/*Import the symbol exported by other module*/

extern int foo;

static int __init my_init(void)
{

	/*pr_info("imported exported module value: %d", toexport);*/
	pr_info("Hello world from mod2: %d\n", foo);

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
