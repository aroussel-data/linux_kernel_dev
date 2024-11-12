#include <linux/module.h>
#include <linux/init.h>
#include <linux/utsname.h>

static int __init my_init(void)
{
	struct list_head *modules;
	struct module *my_module = THIS_MODULE;

	modules = &my_module->list;
	modules = modules->prev;
	
	list_for_each_entry(my_module, modules, list) {
		pr_info("Module name : %s, taints count is: %ld\n", my_module->name, my_module->taints);
	}

	/*pr_info("module loaded\n");*/

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
