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
	{ 0xb9ff86d, "hid_unregister_driver" },
	{ 0x6fe3e8ac, "__hid_register_driver" },
	{ 0x5808c85a, "malloc_sizes" },
	{ 0xfd2249ca, "hid_connect" },
	{ 0x3ecc6f8c, "dev_err" },
	{ 0xa83dfe6b, "dev_set_drvdata" },
	{ 0xbb4f6c53, "kmem_cache_alloc" },
	{ 0x37a0cba, "kfree" },
	{ 0xe5c7b24e, "hid_disconnect" },
	{ 0x8145062c, "input_event" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xec1b4997, "dev_get_drvdata" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("hid:b0003v000009DAp00000006");
MODULE_ALIAS("hid:b0003v000009DAp0000000A");
MODULE_ALIAS("hid:b0003v000009DAp0000001A");
