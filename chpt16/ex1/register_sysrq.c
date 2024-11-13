#include <linux/module.h>
#include <linux/init.h>
#include <linux/sysrq.h>
#include <linux/version.h>

/*static void new_function(u8 new_key) {*/
/*	pr_info("Inside new sysrq function\n");*/
/*	pr_info("Key pressed was %c\n", new_key);*/
/*}*/
//
// create a new sysrq struct that maps a handler to a message
/*struct sysrq_key_op my_sysrq_key = {*/
/*	.handler = new_function, */
/*	.help_msg = "this is a help message for new sysrq", */
/*	.action_msg = "this is a action message for new sysrq", */
/*};*/

/*static int __init my_init(void)*/
/*{*/
/*	// register a new letter that will be a valid sysrq*/
/*	register_sysrq_key('x', &my_sysrq_key);*/
/**/
/*	return 0;*/
/*}*/

/*static void __exit my_exit(void)*/
/*{*/
/*	// unregister the sysrq key on module unload*/
/*	pr_info("Unregistering sysrq key\n");*/
/*	unregister_sysrq_key(120, &my_sysrq_key);*/
/*	pr_info("Module unloaded\n");*/
/*}*/

#define MY_SYSRQ_KEY 'x'

static void my_sysrq_handler(u8 key)
{
	pr_info("Hello from function %s\n", __func__);
	pr_info("Key pressed was '%c'\n", key);
}

static struct sysrq_key_op my_sysrq_key_op = {
	.handler = my_sysrq_handler,
	.help_msg = "e(X)ample",
	.action_msg = "eXample action message",
};

static int __init my_init(void)
{
	int rc = register_sysrq_key(MY_SYSRQ_KEY, &my_sysrq_key_op);

	if (rc == 0)
		pr_info("sysrq key registered\n");
	else
		pr_err("sysrq key failed to register\n");
	return rc;
}

static void __exit my_exit(void)
{
	int rc = unregister_sysrq_key(MY_SYSRQ_KEY, &my_sysrq_key_op);

	if (rc == 0)
		pr_info("sysrq key unregistered\n");
	else
		pr_err("sysrq key failed to unregister\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Alex");
MODULE_LICENSE("GPL v2");
