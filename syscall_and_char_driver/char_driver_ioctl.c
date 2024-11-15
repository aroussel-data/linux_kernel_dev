#include <linux/module.h>	/* for modules */
#include <linux/fs.h>		/* file_operations */
#include <linux/init.h>		/* module_init, module_exit */
#include <linux/device.h>	/* class create, destroy to make nodes */
#include <linux/miscdevice.h>

#define MYDEV_NAME "mycdrv"

/*Write a basic character driver*/

static inline long
mycdrv_unlocked_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{
	pr_info(" I entered the ioctl with cmd=%d, do what you want!\n", cmd);
	return 0;
}

static const struct file_operations mycdrv_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = mycdrv_unlocked_ioctl,
};

static struct miscdevice my_misc_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = MYDEV_NAME,
	.fops = &mycdrv_fops,
};

static int __init my_init(void)
{
	if (misc_register(&my_misc_device)) {
		pr_err("Couldn't register device misc %d.\n",
		       my_misc_device.minor);
		return -EBUSY;
	}

	pr_info("\nSucceeded in registering character device %s\n", MYDEV_NAME);
	return 0;
}

static void __exit my_exit(void)
{
	misc_deregister(&my_misc_device);
	pr_info("\ndevice unregistered\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Alex");
