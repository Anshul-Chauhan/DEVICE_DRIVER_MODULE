// Initialisation functions
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>
//#include <linux/interrupt.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANSHUL");

//#define NAME ANSH  .
//#define SUCCESS 1
//#define DEBOUNCE_TIME 200
static unsigned int gpioLED = 29;
static unsigned int gpioSwitch = 33;
//static bool gpioVal = 0;

//unsigned long IRQflags = IRQF_TRIGGER_RISING;
static int irqNumber, numberPresses;

// interrupt handler prototype
//static irq_handler_t MyInterruptHandler (unsigned int irq, void *dev_id, struct pt_regs *regs);

// Init Module
static int __init CharDevice_init(void)
{
    int result;

    if (!gpio_is_valid(gpioLED))
    {
        printk(KERN_INFO "GPIO_TEST: invalid LED GPIO\n");
        return -ENODEV;
    }
    gpio_request(gpioLED, "GPIO_29");    // gpioLED is hardcoded to 29, request it
    gpio_direction_output(gpioLED, 1);   // set the gpio to be in output mode and on
    // gpio_set_value(gpioLED, ledOn);   
    gpio_export(gpioLED, false);

    //if (!gpio_is_valid(gpioSwitch))
    //{
    //    printk(KERN_INFO "GPIO_TEST: invalid Switch GPIO\n");
    //    return -ENODEV;
    //}
    //gpio_request(gpioSwitch, "GPIO_33");  // gpioLED is hardcoded to 33, request it
    //gpio_direction_input(gpioSwitch);     // set the gpio to be in input mode
    //gpio_set_debounce(gpioSwitch, DEBOUNCE_TIME);
    //gpio_export(gpioSwitch, false);

    irqNumber = gpio_to_irq(gpioSwitch);
    printk(KERN_INFO "EBB Button: The button is mapped to IRQ: %d\n", irqNumber);

    // this call requests an interrupt line
    //result = request_irq(irqNumber,    // the interrupt number requested
    //                  (irq_handler_t) MyInterruptHandler,   // the pointer to the handler function defined below
    //                  IRQflags,        // use the custom kernel param to set interrupt type
    //                  "LED-SWITCH HANDLER",   // used in /proc/interrupts to identify the owner
    //                  NULL);           // the *dev_id for shared interrupt lines, NULL is okay

    return 0;
}

// Cleanup Module

void __exit CharDevice_exit(void)
{
    //free_irq(irqNumber, NULL);
    gpio_unexport(gpioLED);
    //gpio_unexport(gpioSwitch);

    printk(KERN_ALERT "All the resources which were allocated have been unregistered.\n");
    return;
}

//static irq_handler_t MyInterruptHandler (unsigned int irq, void *dev_id, struct pt_regs *regs)
//{
//    gpioVal = !gpioVal;          // invert the LED state on each button press
//    gpio_set_value(gpioLED, gpioVal);   // set the physical LED accordingly
//    numberPresses++;             // global counter, will be outputted when the module is unloaded
//    printk(KERN_INFO "LED-SWITCH: Number of interrupts generated: %d\n", numberPresses);
//    return (irq_handler_t) IRQ_HANDLED;   // announce that the IRQ has been handled correctly
//}

// Module over ride functions
module_init(CharDevice_init);
module_exit(CharDevice_exit);