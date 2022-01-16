#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anshul");
MODULE_DESCRIPTION("Module Parameters");

static char *charvar = "anshul";
static int intvar = 18; 

module_param(charvar, charp, S_IRUGO);
module_param(intvar, int, S_IRUGO);

static int __init  module_param_init(void)
{
    printk(KERN_ALERT "Module Initialization\n");
    printk(KERN_ALERT "The value of charvar is %s\n", charvar);
    printk(KERN_ALERT "The value of intvar is %d\n", intvar);
    return 0;
}

static void __exit  module_param_exit(void)
{
    printk(KERN_ALERT "Module Deinitialization\n");
}

module_init(module_param_init);
module_exit(module_param_exit);