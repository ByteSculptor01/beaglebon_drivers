#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/kernel.h>
#include <linux/init.h>

struct spi_device *spi_device;

static int spi_transfer_example(struct spi_device *spi)
{
    uint8_t tx_buffer[2] = {0xAA, 0xBB};  // Data to send
    uint8_t rx_buffer[2] = {0};           // Data received
    struct spi_transfer transfer = {
        .tx_buf = tx_buffer,
        .rx_buf = rx_buffer,
        .len = sizeof(tx_buffer),
        .speed_hz = 1000000,  // 1 MHz
        .bits_per_word = 8,
    };
    struct spi_message message;

    spi_message_init(&message);
    spi_message_add_tail(&transfer, &message);

    if (spi_sync(spi, &message) < 0) {
        printk(KERN_ERR "SPI Transfer Failed\n");
        return -1;
    }

    printk(KERN_INFO "SPI Transfer Success: Received: 0x%X 0x%X\n", rx_buffer[0], rx_buffer[1]);

    return 0;
}

static int __init spi_comm_init(void)
{
    struct spi_master *master;
    int bus_num = 0;  // SPI bus number
    int cs = 0;       // Chip select

    printk(KERN_INFO "SPI Comm: Initializing\n");

    master = spi_busnum_to_master(bus_num);
    if (!master) {
        printk(KERN_ERR "SPI Comm: Could not get SPI master for bus %d\n", bus_num);
        return -ENODEV;
    }

    spi_device = spi_alloc_device(master);
    if (!spi_device) {
        printk(KERN_ERR "SPI Comm: Could not allocate SPI device\n");
        return -ENOMEM;
    }

    spi_device->chip_select = cs;
    spi_device->max_speed_hz = 1000000;  // 1 MHz
    spi_device->mode = SPI_MODE_0;
    spi_device->bits_per_word = 8;

    snprintf(spi_device->modalias, sizeof(spi_device->modalias), "spidev");

    if (spi_add_device(spi_device) < 0) {
        printk(KERN_ERR "SPI Comm: Failed to add SPI device\n");
        spi_dev_put(spi_device);
        return -1;
    }

    spi_transfer_example(spi_device);

    return 0;
}

static void __exit spi_comm_exit(void)
{
    if (spi_device) {
        spi_unregister_device(spi_device);
    }
    printk(KERN_INFO "SPI Comm: Exiting\n");
}

module_init(spi_comm_init);
module_exit(spi_comm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hetal");
MODULE_DESCRIPTION("A simple SPI communication modul in LKM");
