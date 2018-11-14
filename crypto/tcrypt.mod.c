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
	{ 0x72aa82c6, "param_ops_charp" },
	{ 0x3ec8886f, "param_ops_int" },
	{ 0xc3fe87c8, "param_ops_uint" },
	{ 0x4302d0eb, "free_pages" },
	{ 0x93fca811, "__get_free_pages" },
	{ 0x5086ac3a, "alg_test" },
	{ 0x90a1004a, "crypto_has_alg" },
	{ 0x5808c85a, "malloc_sizes" },
	{ 0xb7c1715c, "crypto_ahash_digest" },
	{ 0x539289ba, "crypto_ahash_final" },
	{ 0x37a0cba, "kfree" },
	{ 0x7a4497db, "kzfree" },
	{ 0xec6a4d04, "wait_for_completion_interruptible" },
	{ 0xf6288e02, "__init_waitqueue_head" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x6ac37555, "crypto_alloc_ahash" },
	{ 0xbb4f6c53, "kmem_cache_alloc" },
	{ 0x2196324, "__aeabi_idiv" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0x60f71cfa, "complete" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x7d11c268, "jiffies" },
	{ 0x799aca4, "local_bh_enable" },
	{ 0x3ff62317, "local_bh_disable" },
	{ 0x7fec5a87, "crypto_destroy_tfm" },
	{ 0x9d669763, "memcpy" },
	{ 0xbfe9d015, "crypto_alloc_base" },
	{ 0x27e1a049, "printk" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x6ccf7bd7, "__pv_phys_offset" },
	{ 0xbb7a8ac4, "mem_map" },
	{ 0xc27487dd, "__bug" },
	{ 0x5f754e5a, "memset" },
	{ 0xf88c3301, "sg_init_table" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

