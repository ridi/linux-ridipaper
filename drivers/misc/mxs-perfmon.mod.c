#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x523eafe8, "module_layout" },
	{ 0x3900e0d5, "platform_driver_unregister" },
	{ 0xd0d641fc, "platform_driver_register" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0x9d669763, "memcpy" },
	{ 0x996bdb64, "_kstrtoul" },
	{ 0x97255bdf, "strlen" },
	{ 0x71c90087, "memcmp" },
	{ 0xf998eb2b, "mxs_reset_block" },
	{ 0xb0af4446, "clk_enable" },
	{ 0xdc10a620, "sysfs_create_group" },
	{ 0xb5e0710f, "clk_get" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xe440476f, "platform_get_resource" },
	{ 0x37a0cba, "kfree" },
	{ 0x2e1ca751, "clk_put" },
	{ 0x17b4cbac, "clk_disable" },
	{ 0xa83dfe6b, "dev_set_drvdata" },
	{ 0x40777185, "sysfs_remove_group" },
	{ 0xec1b4997, "dev_get_drvdata" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

