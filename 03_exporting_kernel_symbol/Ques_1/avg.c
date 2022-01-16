#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include"add.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anshul");
MODULE_DESCRIPTION("Export Symbol Module");

int a = 34;
int b = 82;

static int __init  avg_init(void)
{
    printk(KERN_ALERT "Module Initialization\n");
    printk(KERN_ALERT "Average of %d and %d is %d\n", a, b, add(a, b)/2);
    return 0;
}

static void __exit  avg_exit(void)
{
    printk(KERN_ALERT "Module Deinitialization\n");
}

module_init(avg_init);
module_exit(avg_exit);