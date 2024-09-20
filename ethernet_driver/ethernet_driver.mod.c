#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x3726c6aa, "module_layout" },
	{ 0x462c7f8a, "unregister_netdev" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xb4aec65, "init_net" },
	{ 0xb2c317e1, "free_netdev" },
	{ 0x39b689a3, "register_netdev" },
	{ 0xd84fb0f1, "ether_setup" },
	{ 0x8e620df3, "alloc_etherdev_mqs" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x4fad61, "consume_skb" },
	{ 0xc5850110, "printk" },
};

MODULE_INFO(depends, "");

