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
	{ 0x7ee153a2, "unregister_nls" },
	{ 0xdc3b8bf1, "register_nls" },
	{ 0xfcc2a43c, "utf32_to_utf8" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xb2682405, "utf8_to_utf32" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

