// Initialisation functions
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include "ioctl.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANSHUL");

#define NAME MyIOCTLdevice1
#define SUCCESS 0

// Function Prototypes
int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
ssize_t NAME_write(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos);
ssize_t NAME_read(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos);
long NAME_ioctl (struct file *filp, unsigned int command, unsigned long arg);

struct DefaultData
{
    int BaudRate;
    int StopBits;
    int Parity;
};

// Structure that defines the operations provided by the driver
struct file_operations fops =
{
    .open = NAME_open,
    .read = NAME_read,
    .write = NAME_write,
    .unlocked_ioctl = NAME_ioctl,
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
    DevNo = MKDEV(259, 0); 
    MAJOR = MAJOR(DevNo);
    MINOR = MINOR(DevNo);
    printk(KERN_ALERT "The Major number is %d and the Minor number is %d.\n", MAJOR, MINOR);
    result = register_chrdev_region(DevNo, 1, "MyIOCTLdevice1"); // register device region
    if(result < 0)
    {
        printk(KERN_ALERT "Requested region is not obtainable.\n");
        return (-1);
    }

    my_cdev = cdev_alloc(); 
    my_cdev->ops = &fops;   

    result = cdev_add(my_cdev, DevNo, 1); 
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
    DevNo = MKDEV(259, 0); 
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

// read functionality
ssize_t NAME_read(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[] = "Data writing into user space ioctl application from kernel space.";
    unsigned long result;
    ssize_t retval;
    result = copy_to_user((char *)Ubuf, (char *)Kbuf, sizeof(Kbuf));
    if(result == 0)
    {
        printk(KERN_ALERT "Data successfully read.\n");
        retval = count;
        return retval;
    }
    else if(result > 0)
    {
        printk(KERN_ALERT "Partial data read.\n");
        retval = (count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "Error writing data to user.\n");
        retval = -EFAULT;
        return retval;
    }
}

// write functionality
ssize_t NAME_write(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[80];
    unsigned long result;
    ssize_t retval;
    result = copy_from_user((char *)Kbuf, (char *)Ubuf, count); 
    if(result == 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        printk(KERN_ALERT "Data successfully written.\n");
        retval = count;
        return retval;
    }
    else if(result > 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        printk(KERN_ALERT "Partial data written.\n");
        retval = (count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "Error writing data to kernel.\n");
        retval = -EFAULT;
        return retval;
    }
}

long NAME_ioctl (struct file *filp, unsigned int command, unsigned long arg)
{
    unsigned int temp, STOP_BITS;
    ssize_t retval = SUCCESS;
    char Ubuf[20];
    struct DefaultData *ToSend;
    printk("IOCTL function.\n");
    switch(command)
    {
        case SET_BAUD_RATE:
            get_user(temp, (int __user *)arg);
            printk("Setting the Baud Rate to %d\n", temp);
            temp = 10;
            put_user(temp, (int __user *)arg);
            break;
        case SET_NO_OF_STOP_BITS:
            get_user(STOP_BITS, (int __user *)arg);
            printk("Setting the number of stop bits to %d.\n", STOP_BITS);
            break;
        case SET_DIRECTION_WRITE:
            printk("The direction is set to write.\n");
            break;
        case DEFAULT_DATA:
            ToSend = (struct DefaultData *)Ubuf;
            copy_from_user(Ubuf, (struct DefaultData *)arg, sizeof(struct DefaultData));
            printk("Default Baud Rate: %d.\n", ToSend->BaudRate);
            printk("Default Stop Bits: %d.\n", ToSend->StopBits);
            printk("Default Parity: %d.\n", ToSend->Parity);
            break;
        default:
            printk("Command not found.\n");
            return (-EINVAL);
    }
    return (retval);
}

module_init(CharDevice_init);
module_exit(CharDevice_exit);