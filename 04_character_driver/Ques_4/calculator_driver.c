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

int sum = 0;
int sub = 0;
int mul = 1;
int div = 1;
dev_t DevNo;
int MAJOR, MINOR;

// Function Prototypes
int open(struct inode *inode, struct file *filp);
int release(struct inode *inode, struct file *filp);

ssize_t write_add(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos);
ssize_t read_add(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos);

ssize_t write_sub(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos);
ssize_t read_sub(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos);

ssize_t write_mul(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos);
ssize_t read_mul(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos);

ssize_t write_div(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos);
ssize_t read_div(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos);

// Structure that defines the operations provided by the driver
struct file_operations fops =
{
    .open = open,
    .read = NULL,
    .write = NULL,
    .release = release,
};

// Structure for a character driver
struct cdev *cdev;

// Init Module
static int __init CharDevice_init(void)
{
    int result;
    result = alloc_chrdev_region(&DevNo, 0, 4, "MyCharDevice3");
    if(result < 0)
    {
        printk(KERN_ALERT "Requested region is not obtainable.\n");
        return (-1);
    }
    MAJOR = MAJOR(DevNo);
    MINOR = MINOR(DevNo);
    printk(KERN_ALERT "Device 1: The Major number is %d and the Minor number is %d.\n", MAJOR, MINOR);
    cdev = cdev_alloc(); // allocate memory to char device structure
    cdev->ops = &fops;   // link our file operations to the char device

    result = cdev_add(cdev, DevNo, 4); // Notify the kernel about the new device
    if(result < 0)
    {
        printk(KERN_ALERT "The char device has not been created.\n");
        unregister_chrdev_region(DevNo, 4);
        return (-1);
    }

    return 0;
}

// Cleanup Module
void __exit CharDevice_exit(void)
{
    //int MAJOR, MINOR, MAJORs, MINORs, MAJORm, MINORm, MAJORd, MINORd;
    MAJOR = MAJOR(DevNo);
    MINOR = MINOR(DevNo);
    printk(KERN_ALERT "DEvice 1: The Major number is %d and the Minor number is %d.\n", MAJOR, MINOR);
    unregister_chrdev_region(DevNo, 4); // unregister the device number and the device created
    cdev_del(cdev);
    return;
}

// open system call
int open(struct inode *inode, struct file *filp)
{
    if(MINOR(inode->i_rdev) == 0)
    {
        fops.read = read_add;
        fops.write = write_add;
        printk(KERN_ALERT "Device 1: In kernel open system call has been executed.\n");
    }
    else if(MINOR(inode->i_rdev) == 1)
    {
        fops.read = read_sub;
        fops.write = write_sub;
        printk(KERN_ALERT "Device 2: In kernel open system call has been executed.\n");
    }
    else if(MINOR(inode->i_rdev) == 2)
    {
        fops.read = read_mul;
        fops.write = write_mul;
        printk(KERN_ALERT "Device 3: In kernel open system call has been executed.\n");
    }
    else if(MINOR(inode->i_rdev) == 3)
    {
        fops.read = read_div;
        fops.write = write_div;
        printk(KERN_ALERT "Device 4: In kernel open system call has been executed.\n");
    }
    else
    {
        return (-1);
    }
    
    return 0;
}


// close system call
int release(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "In kernel release system call has been executed.\n");
    return 0;
}

// read functionality
ssize_t read_add(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[50];
    sprintf(Kbuf, "%d", sum);
    sum = 0;
    printk("sum = %d\n", sum);
    unsigned long result;
    ssize_t retval;
    result = copy_to_user((char *)Ubuf, (char *)Kbuf, sizeof(Kbuf)); // copy data to user
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

ssize_t read_sub(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[50];
    sprintf(Kbuf, "%d", sub);
    sub = 0;
    printk("sub = %d\n", sub);
    unsigned long result;
    ssize_t retval;
    result = copy_to_user((char *)Ubuf, (char *)Kbuf, sizeof(Kbuf)); // copy data to user
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

ssize_t read_mul(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[50];
    sprintf(Kbuf, "%d", mul);
    mul = 1;
    printk("mul = %d\n", mul);
    unsigned long result;
    ssize_t retval;
    result = copy_to_user((char *)Ubuf, (char *)Kbuf, sizeof(Kbuf)); // copy data to user
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

ssize_t read_div(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[50];
    sprintf(Kbuf, "%d", div);
    div = 1;
    printk("div = %d\n", div);
    unsigned long result;
    ssize_t retval;
    result = copy_to_user((char *)Ubuf, (char *)Kbuf, sizeof(Kbuf)); // copy data to user
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
ssize_t write_add(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[80];
    int a;
    unsigned long result;
    ssize_t retval;
    result = copy_from_user((char *)Kbuf, (char *)Ubuf, count); // copy data from user
    if(result == 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        sscanf(Kbuf, "%d", &a);
        sum = sum + a;
        printk("sum = %d", sum); 
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

ssize_t write_sub(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[80];
    int a;
    unsigned long result;
    ssize_t retval;
    result = copy_from_user((char *)Kbuf, (char *)Ubuf, count); // copy data from user
    if(result == 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        sscanf(Kbuf, "%d", &a);
        if(sub == 0)
            sub = a;
        else
            sub = sub - a;
        printk("sub = %d", sub); 
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

ssize_t write_mul(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[80];
    int a;
    unsigned long result;
    ssize_t retval;
    // strcpy(Kbuf, Ubuf);
    result = copy_from_user((char *)Kbuf, (char *)Ubuf, count); // copy data from user
    if(result == 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        sscanf(Kbuf, "%d", &a);
        mul = mul * a;
        printk("mul = %d", mul); 
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

ssize_t write_div(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[80];
    int a;
    unsigned long result;
    ssize_t retval;
    // strcpy(Kbuf, Ubuf);
    result = copy_from_user((char *)Kbuf, (char *)Ubuf, count); // copy data from user
    if(result == 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        sscanf(Kbuf, "%d", &a);
        if(div == 1)
            div = a;
        else
            div = div / a;
        printk("div = %d", div); 
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

// Module over ride functions
module_init(CharDevice_init);
module_exit(CharDevice_exit);
