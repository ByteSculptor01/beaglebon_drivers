#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/interrupt.h>
#include <linux/io.h>

#define DRV_NAME "simple_ethernet"

struct simple_eth_priv {
    void __iomem *base_addr;
    struct net_device *ndev;
    int irq;
};

/* This function will be called when the interface is activated */
static int simple_eth_open(struct net_device *ndev) {
    printk(KERN_INFO DRV_NAME ": Opening interface %s\n", ndev->name);
    netif_start_queue(ndev);
    return 0;
}

/* This function will be called when the interface is deactivated */
static int simple_eth_stop(struct net_device *ndev) {
    printk(KERN_INFO DRV_NAME ": Stopping interface %s\n", ndev->name);
    netif_stop_queue(ndev);
    return 0;
}

/* This function will be called to transmit a packet */
static netdev_tx_t simple_eth_start_xmit(struct sk_buff *skb, struct net_device *ndev) {
    printk(KERN_INFO DRV_NAME ": Transmitting packet on %s\n", ndev->name);
    dev_kfree_skb(skb);  // Free the socket buffer after transmission
    return NETDEV_TX_OK;
}

/* This function will be called when an interrupt occurs */
static irqreturn_t simple_eth_interrupt(int irq, void *dev_id) {
    printk(KERN_INFO DRV_NAME ": Interrupt on %s\n", ((struct net_device *)dev_id)->name);
    return IRQ_HANDLED;
}

/* Network device operations structure */
static const struct net_device_ops simple_eth_netdev_ops = {
    .ndo_open       = simple_eth_open,
    .ndo_stop       = simple_eth_stop,
    .ndo_start_xmit = simple_eth_start_xmit,
    .ndo_set_config = NULL, // We won't be implementing set_config in this example
};

/* This function will be called to initialize the device structure */
static void simple_eth_init(struct net_device *ndev) {
    ether_setup(ndev);
    ndev->netdev_ops = &simple_eth_netdev_ops;
}

/* This function will be called when the driver is loaded */
static int __init simple_eth_init_module(void) {
    struct net_device *ndev;
    struct simple_eth_priv *priv;

    ndev = alloc_etherdev(sizeof(struct simple_eth_priv));
    if (!ndev) {
        printk(KERN_ERR DRV_NAME ": Unable to allocate net_device\n");
        return -ENOMEM;
    }

    priv = netdev_priv(ndev);
    priv->ndev = ndev;

    strcpy(ndev->name, "eth%d");

    simple_eth_init(ndev);

    if (register_netdev(ndev)) {
        printk(KERN_ERR DRV_NAME ": Unable to register net_device\n");
        free_netdev(ndev);
        return -ENODEV;
    }

    printk(KERN_INFO DRV_NAME ": Ethernet driver loaded\n");
    return 0;
}

/* This function will be called when the driver is unloaded */
static void __exit simple_eth_cleanup_module(void) {
    struct net_device *ndev;
    struct simple_eth_priv *priv;

    ndev = first_net_device(&init_net);
    while (ndev) {
        if (strcmp(ndev->name, "eth%d") == 0) {
            priv = netdev_priv(ndev);
            unregister_netdev(ndev);
            free_netdev(ndev);
            break;
        }
        ndev = next_net_device(ndev);
    }

    printk(KERN_INFO DRV_NAME ": Ethernet driver unloaded\n");
}

module_init(simple_eth_init_module);
module_exit(simple_eth_cleanup_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hetal");
MODULE_DESCRIPTION("A simple Ethernet driver example");
