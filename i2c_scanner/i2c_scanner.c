#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init i2c_scanner_init(void)
{
    struct i2c_adapter *adap;
    struct i2c_msg msg;
    uint8_t addr;
    int ret;
    int bus_num = 2; // Change this to the I2C bus number you want to scan

    printk(KERN_INFO "I2C Scanner: Initializing\n");

    adap = i2c_get_adapter(bus_num);
    if (!adap) {
        printk(KERN_ERR "I2C Scanner: Could not get I2C adapter for bus %d\n", bus_num);
        return -ENODEV;
    }

    for (addr = 0x03; addr < 0x78; addr++) {
        msg.addr = addr;
        msg.flags = 0;
        msg.len = 0;
        msg.buf = NULL;

        ret = i2c_transfer(adap, &msg, 1);
        if (ret == 1) {
            printk(KERN_INFO "I2C Scanner: Found device at address 0x%02x\n", addr);
        }
    }

    i2c_put_adapter(adap);

    return 0;
}

static void __exit i2c_scanner_exit(void)
{
    printk(KERN_INFO "I2C Scanner: Exiting\n");
}

module_init(i2c_scanner_init);
module_exit(i2c_scanner_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hetal");
MODULE_DESCRIPTION("A simple I2C bus scanner in LKM");

