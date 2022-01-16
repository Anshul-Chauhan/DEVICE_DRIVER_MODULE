#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anshul");
MODULE_DESCRIPTION("Export Symbol Module");

int a = 18;
int b = 36;

int add(int a, int b)
{
    return a + b;
}

EXPORT_SYMBOL_GPL(add);

static int __init  add_init(void)
{
    printk(KERN_ALERT "Module Initialization\n");
    printk(KERN_ALERT "Addition of %d and %d is %d\n", a, b, add(a, b));
    return 0;
}

static void __exit  add_exit(void)
{
    printk(KERN_ALERT "Module Deinitialization\n");
}

module_init(add_init);
module_exit(add_exit);