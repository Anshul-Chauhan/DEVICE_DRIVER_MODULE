// Initialisation functions
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/completion.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANSHUL");

#define NAME ComplCharDevice1
char Kbuf[100];  // shared resourse
int sum = 0;
int flag = 0;

// structure for completion
struct completion task1, task2, task3;

// Function Prototypes
int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
ssize_t NAME_write(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos);
ssize_t NAME_read(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos);

// Structure that defines the operations provided by the driver
struct file_operations fops =
{
    .open = NAME_open,
    .read = NAME_read,
    .write = NAME_write,
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
    DevNo = MKDEV(277, 0); // Statically creating a device number
    MAJOR = MAJOR(DevNo);
    MINOR = MINOR(DevNo);
    printk(KERN_ALERT "The Major number is %d and the Minor number is %d.\n", MAJOR, MINOR);
    result = register_chrdev_region(DevNo, 1, "ComplCharDevice1"); // register device region
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

    init_completion(&task1); // Dynamically initialising the completion
    init_completion(&task2);
    init_completion(&task3);
    return 0;
}

// Cleanup Module
void __exit CharDevice_exit(void)
{
    int MAJOR, MINOR;
    dev_t DevNo;
    DevNo = MKDEV(277, 0); // Statically creating a device number
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
    wait_for_completion(&task1);
    wait_for_completion(&task2);
    wait_for_completion(&task3);
    sprintf(Kbuf, "%d", sum);
    unsigned long result;
    ssize_t retval;
    result = copy_to_user((char *)Ubuf, (char *)Kbuf, sizeof(Kbuf)); // copy data to user
    sum = 0;
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
    int num;
    unsigned long result;
    ssize_t retval;
    if(flag == 0)
    {
        result = copy_from_user((char *)Kbuf, (char *)Ubuf, count); // copy data from user
        sscanf(Kbuf, "%d", &num);
        if(result == 0)
        {
            printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
            printk(KERN_ALERT "Data successfully written.\n");
            retval = count;
            flag++;
            sum = sum + num;
            complete(&task1);
            printk("Sending completion signal for task 1\n");
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

    if(flag == 1)
    {
        result = copy_from_user((char *)Kbuf, (char *)Ubuf, count); // copy data to user
        sscanf(Kbuf, "%d", &num);
        if(result == 0)
        {
            printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
            printk(KERN_ALERT "Data successfully written.\n");
            retval = count;
            flag++;
            sum = sum + num;
            complete(&task2);
            printk("Sending completion signal for task 2\n");
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

    if(flag == 2)
    {
        result = copy_from_user((char *)Kbuf, (char *)Ubuf, count); // copy data to user
        sscanf(Kbuf, "%d", &num);
        if(result == 0)
        {
            printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
            printk(KERN_ALERT "Data successfully written.\n");
            retval = count;
            flag = 0;
            sum = sum + num;
            complete(&task3);
            printk("Sending completion signal for task 3\n");
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
    return 0;
}

// Module over ride functions
module_init(CharDevice_init);
module_exit(CharDevice_exit);