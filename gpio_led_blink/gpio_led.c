#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/err.h>

#define GPIO_LED 53  // GPIO pin number (replace with the correct pin number for your setup)

static struct task_struct *task;

// Thread function to blink the LED
static int blink_thread(void *arg)
{
    int state = 0;
    while (!kthread_should_stop()) {
        gpio_set_value(GPIO_LED, state);
        state = !state;
        msleep(1000);  // Delay for 1000 milliseconds
    }
    return 0;
}

static int __init gpio_led_init(void)
{
    int ret;

    printk(KERN_INFO "Initializing GPIO LED Blink Module\n");

    // Request the GPIO
    ret = gpio_request(GPIO_LED, "sysfs");
    if (ret) {
        printk(KERN_ERR "GPIO request failed: %d\n", ret);
        return ret;
    }

    // Set the GPIO direction to output
    ret = gpio_direction_output(GPIO_LED, 0);
    if (ret) {
        printk(KERN_ERR "GPIO direction set failed: %d\n", ret);
        gpio_free(GPIO_LED);
        return ret;
    }

    // Start the LED blink thread
    task = kthread_run(blink_thread, NULL, "LED Blink Thread");
    if (IS_ERR(task)) {
        printk(KERN_ERR "Failed to create thread: %ld\n", PTR_ERR(task));
        gpio_free(GPIO_LED);
        return PTR_ERR(task);
    }

    return 0;
}

static void __exit gpio_led_exit(void)
{
    printk(KERN_INFO "Exiting GPIO LED Blink Module\n");

    // Stop the thread
    kthread_stop(task);

    // Set the GPIO to low before exiting
    gpio_set_value(GPIO_LED, 0);

    // Free the GPIO
    gpio_free(GPIO_LED);
}

module_init(gpio_led_init);
module_exit(gpio_led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hetal");
MODULE_DESCRIPTION("A simple GPIO LED Blink LKM");
