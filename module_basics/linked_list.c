#include <linux/module.h>
#include <linux/atomic.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/init.h>

/*Playing around with the list head macro to more safely create and navigate linked list data structure*/

LIST_HEAD(my_list);

struct my_entry {
	struct list_head list;
	int intvar;
};

static int __init my_init(void)
{
	struct my_entry *me;
	int j;

	for (j=0; j< 5; j++) {
		me = kmalloc(sizeof(struct my_entry), GFP_KERNEL);
		me->intvar = j;
		list_add(&me->list, &my_list);
	};

	struct list_head *list;	/* pointer to list head object */

	list_for_each(list, &my_list) {
		struct my_entry *me = list_entry(list, struct my_entry, list);
		pr_info("Entry value: %d\n", me->intvar);
		kfree(me);
	}

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
