// Initialisation functions
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANSHUL");

#define NAME MyCharDevice1

// Function Prototypes
int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);

// Structure that defines the operations provided by the driver
struct file_operations fops =
{
    .open = NAME_open,
    .release = NAME_release,
};

// Structure for a character driver
struct cdev *my_cdev;

// Init Module
static int __init CharDevice_init(void)
{
    int result;
    int MAJOR, MINOR;
    dev_t DevNo;
    DevNo = MKDEV(256, 0); // Statically creating a device number
    MAJOR = MAJOR(DevNo);
    MINOR = MINOR(DevNo);
    printk(KERN_ALERT "The Major number is %d and the Minor number is %d.\n", MAJOR, MINOR);
    result = register_chrdev_region(DevNo, 1, "MyCharDevice1"); // register device region
    if(result < 0)
    {
        printk(KERN_ALERT "Requested region is not obtainable.\n");
        return (-1);
    }

    my_cdev = cdev_alloc(); // allocate memory to char device structure
    my_cdev->ops = &fops; // link our file operations to the char device

    result = cdev_add(my_cdev, DevNo, 1); // Notify the kernel about the new device
    if(result < 0)
    {
        printk(KERN_ALERT "The char device has not been created.\n");
        unregister_chrdev_region(DevNo, 1);
        return (-1);
    }
    return 0;
}

// Cleanup Module
void __exit CharDevice_exit(void)
{
    int MAJOR, MINOR;
    dev_t DevNo;
    DevNo = MKDEV(256, 0); // Statically creating a device number
    MAJOR = MAJOR(DevNo);
    MINOR = MINOR(DevNo);
    printk(KERN_ALERT "The Major number is %d and the Minor number is %d.\n", MAJOR, MINOR);
    unregister_chrdev_region(DevNo, 1); // unregister the device number and the device created
    cdev_del(my_cdev);
    printk(KERN_ALERT "All the resources which were allocated have been unregistered.\n");
    return;
}

// open system call
int NAME_open(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "In kernel open system call has been executed.\n");
    return 0;
}

// close system call
int NAME_release(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "In kernel release system call has been executed.\n");
    return 0;
}

// Module over ride functions
module_init(CharDevice_init);
module_exit(CharDevice_exit);
