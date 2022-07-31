/* simple.c – Our First Driver code */

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

static int __init simple_init(void) /* Constructor */
{
    printk(KERN_INFO "simple registered");

    return 0;
}

static void __exit simple_exit(void) /* Destructor */
{
    printk(KERN_INFO "simple unregistered");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Oleg Solomka <legomushroom@gmail.com>");
MODULE_DESCRIPTION("Simple driver.");
