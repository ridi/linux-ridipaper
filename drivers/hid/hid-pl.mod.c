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
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xfd2249ca, "hid_connect" },
	{ 0x3ecc6f8c, "dev_err" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("hid:b0003v00000810p00000001");
MODULE_ALIAS("hid:b0003v00000810p00000002");
MODULE_ALIAS("hid:b0003v00000E8Fp00000003");
