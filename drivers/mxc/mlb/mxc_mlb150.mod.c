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
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x546ae5c3, "iram_free" },
	{ 0xb9e52429, "__wake_up" },
	{ 0x5808c85a, "malloc_sizes" },
	{ 0xa83dfe6b, "dev_set_drvdata" },
	{ 0xb5e0710f, "clk_get" },
	{ 0xe7b088cf, "regulator_enable" },
	{ 0x8803904, "regulator_set_voltage" },
	{ 0xf26066ea, "regulator_get" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0xe440476f, "platform_get_resource" },
	{ 0xfe3f6c61, "device_create" },
	{ 0xe074de84, "__class_create" },
	{ 0xddab95d4, "cdev_add" },
	{ 0xdb11e6a6, "cdev_init" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0x3ecc6f8c, "dev_err" },
	{ 0xbb4f6c53, "kmem_cache_alloc" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x8893fa5d, "finish_wait" },
	{ 0x75a17bed, "prepare_to_wait" },
	{ 0x1000e51, "schedule" },
	{ 0x27e1a049, "printk" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x29338e18, "iram_alloc" },
	{ 0x37a0cba, "kfree" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x799d58f9, "class_destroy" },
	{ 0x3a113c47, "device_destroy" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x45a55ec8, "__iounmap" },
	{ 0x74b1617f, "gpio_mlb_inactive" },
	{ 0x25048e2c, "regulator_put" },
	{ 0x5102a693, "regulator_disable" },
	{ 0x2e1ca751, "clk_put" },
	{ 0x17b4cbac, "clk_disable" },
	{ 0xb0af4446, "clk_enable" },
	{ 0xec1b4997, "dev_get_drvdata" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

