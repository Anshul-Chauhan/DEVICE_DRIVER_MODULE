#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anshul");
MODULE_DESCRIPTION("Module Parameters");

static int arr[5];
static int i;

module_param_array(arr, int, NULL, S_IRUGO);

static int __init  array_init(void)
{
    printk(KERN_ALERT "Module Initialization\n");
    for(i = 0; i < (sizeof(arr)/sizeof(int)); i++)
    {
        printk(KERN_ALERT "Element %d of array is %d\n", i+1, arr[i]);
    }
    return 0;
}

static void __exit  array_exit(void)
{
    printk(KERN_ALERT "Module Deinitialization\n");
}

module_init(array_init);
module_exit(array_exit);