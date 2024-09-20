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
	{ 0x7e2e8c4d, "spi_unregister_device" },
	{ 0x2bf7ac59, "put_device" },
	{ 0x2d4bb8e3, "spi_add_device" },
	{ 0xe914e41e, "strcpy" },
	{ 0x23c6c846, "spi_alloc_device" },
	{ 0x34084c26, "spi_busnum_to_master" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0xc5850110, "printk" },
	{ 0xd8d9e769, "spi_sync" },
	{ 0x68f31cbd, "__list_add_valid" },
	{ 0x5f754e5a, "memset" },
};

MODULE_INFO(depends, "");

