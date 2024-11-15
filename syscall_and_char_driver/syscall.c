#include <linux/module.h>
#include <linux/init.h>
#include <linux/unistd.h>

void *save_stub;

struct my_sc_struct {
	long (*fun)(unsigned long p1);
};

extern struct my_sc_struct my_sc;

static long test_syscall(unsigned long p1)
{
	long rc;

	rc = 100 * p1;
	pr_info("in %s, p1, rc= %ld, %ld\n", __func__, p1, rc);
	return rc;
}

static int __init my_init(void)
{
	struct my_sc_struct *s = &my_sc;

	pr_info("Loading module\n");
	pr_info("s->fun = %p\n", s->fun);
	save_stub = s->fun;
	s->fun = test_syscall;
	pr_info("s->fun = %p\n", s->fun);
	return 0;
}

static void __exit my_exit(void)
{
	struct my_sc_struct *s = &my_sc;

	pr_info("Unloading module\n");
	pr_info("s->fun = %p\n", s->fun);
	s->fun = save_stub;
	pr_info("Restored the original system call");
	pr_info("s->fun = %p\n", s->fun);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Alex");
MODULE_LICENSE("GPL v2");
