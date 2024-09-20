#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/serial_reg.h>
#include <linux/errno.h>

#define UART_BASE_ADDR 0x48022000  // Base address for UART1 on BeagleBone Black
#define UART_CLOCK 48000000       // UART clock frequency

static struct cdev uart_cdev;
static dev_t dev_num;

static int uart_open(struct inode *inode, struct file *file) {
    pr_info("UART: Device opened\n");
    return 0;
}

static int uart_release(struct inode *inode, struct file *file) {
    pr_info("UART: Device closed\n");
    return 0;
}

static ssize_t uart_write(struct file *file, const char __user *buf, size_t len, loff_t *off) {
    void __iomem *uart_base;
    char data;

    uart_base = ioremap(UART_BASE_ADDR, 0x1000);

    if (copy_from_user(&data, buf, 1))
        return -EFAULT;

    while (!(readl(uart_base + UART_LSR) & UART_LSR_THRE))
        cpu_relax();

    writel(data, uart_base + UART_TX);

    iounmap(uart_base);
    pr_info("UART: Sent data: %c\n", data);

    return 1;
}

static ssize_t uart_read(struct file *file, char __user *buf, size_t len, loff_t *off) {
    void __iomem *uart_base;
    char data;

    uart_base = ioremap(UART_BASE_ADDR, 0x1000);

    while (!(readl(uart_base + UART_LSR) & UART_LSR_DR))
        cpu_relax();

    data = readl(uart_base + UART_RX);

    if (copy_to_user(buf, &data, 1))
        return -EFAULT;

    iounmap(uart_base);
    pr_info("UART: Received data: %c\n", data);

    return 1;
}

static struct file_operations uart_fops = {
    .owner = THIS_MODULE,
    .open = uart_open,
    .release = uart_release,
    .write = uart_write,
    .read = uart_read,
};

static int __init uart_driver_init(void) {
    int ret;

    ret = alloc_chrdev_region(&dev_num, 0, 1, "uart_device");
    if (ret < 0) {
        pr_err("UART: Failed to allocate device number\n");
        return ret;
    }

    cdev_init(&uart_cdev, &uart_fops);
    uart_cdev.owner = THIS_MODULE;

    ret = cdev_add(&uart_cdev, dev_num, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev_num, 1);
        pr_err("UART: Failed to add cdev\n");
        return ret;
    }

    pr_info("UART: Driver initialized\n");
    return 0;
}

static void __exit uart_driver_exit(void) {
    cdev_del(&uart_cdev);
    unregister_chrdev_region(dev_num, 1);
    pr_info("UART: Driver exited\n");
}

module_init(uart_driver_init);
module_exit(uart_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hetal");
MODULE_DESCRIPTION("A simple UART driver in LKM");
