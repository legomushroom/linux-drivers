#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

static dev_t first; // Global variable for the first device number
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class

static int my_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "ch: open()\n");
	return 0;
}
static int my_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "ch: close()\n");
	return 0;
}
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "ch: read()\n");
	return 0;
}
static ssize_t my_write(struct file *f, const char __user *buf, size_t len,
	loff_t *off)
{
	printk(KERN_INFO "ch: write()\n");
	return len;
}

static struct file_operations pugs_fops =
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write
};

static int __init char_init(void) /* Constructor */
{
	int ret;
	struct device *dev_ret;

	printk(KERN_INFO "ch: registered");
	if ((ret = alloc_chrdev_region(&first, 0, 1, "lego")) < 0)
	{
		printk(KERN_INFO "ch: cannot allocate char dev region");
		return ret;
	}
	printk(KERN_INFO "ch: <Major, Minor>: <%d, %d>\n", MAJOR(first), MINOR(first));

	if (IS_ERR(cl = class_create(THIS_MODULE, "chdrv")))
	{
		printk(KERN_INFO "ch: cannot create chardrv class");

		unregister_chrdev_region(first, 1);

		return PTR_ERR(cl);
	}

	if (IS_ERR(dev_ret = device_create(cl, NULL, first, NULL, "chnull")))
	{
		printk(KERN_INFO "ch: cannot device");

		class_destroy(cl);
		unregister_chrdev_region(first, 1);


		return PTR_ERR(dev_ret);
	}

	printk(KERN_INFO "ch: device initialized");

	cdev_init(&c_dev, &pugs_fops);
	if ((ret = cdev_add(&c_dev, first, 1)) < 0)
	{
		printk(KERN_INFO "ch: cannot add device");

		device_destroy(cl, first);
		class_destroy(cl);
		unregister_chrdev_region(first, 1);

		return ret;
	}

	printk(KERN_INFO "ch: OK");

	return 0;
}

static void __exit char_exit(void) /* Destructor */
{
	printk(KERN_INFO "ch: exit");

	cdev_del(&c_dev);
	device_destroy(cl, first);
	class_destroy(cl);
	unregister_chrdev_region(first, 1);

	printk(KERN_INFO "ch: unregistered");
}

module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oleg Solomka <legomushroom@gmail.com>");
MODULE_DESCRIPTION("Char driver.");
