/* char.c – Our First Driver code */

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

static dev_t first; // Global variable for the first device number

static int __init char_init(void) /* Constructor */
{
    int ret;

    printk(KERN_INFO "char: registered");
    if ((ret = alloc_chrdev_region(&first, 0, 3, "legomushroom")) < 0)
    {
        printk(KERN_INFO "char: cannot allocate char dev region");
        return ret;
    }
    printk(KERN_INFO "char: <Major, Minor>: <%d, %d>\n", MAJOR(first), MINOR(first));
    return 0;
}

static void __exit char_exit(void) /* Destructor */
{
    unregister_chrdev_region(first, 3);
    printk(KERN_INFO "char: unregistered");
}

module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Oleg Solomka <legomushroom@gmail.com>");
MODULE_DESCRIPTION("Char driver.");
