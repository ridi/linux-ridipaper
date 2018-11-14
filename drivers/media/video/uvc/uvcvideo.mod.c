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
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xa83dfe6b, "dev_set_drvdata" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0xfed6a454, "video_device_release" },
	{ 0x4828ca48, "video_usercopy" },
	{ 0x5808c85a, "malloc_sizes" },
	{ 0x52760ca9, "getnstimeofday" },
	{ 0xc4f476d5, "v4l2_device_unregister" },
	{ 0x1ef6eafe, "usb_kill_urb" },
	{ 0xe2fae716, "kmemdup" },
	{ 0xc639e848, "__video_register_device" },
	{ 0x62b72b0d, "mutex_unlock" },
	{ 0xc6e6680f, "usb_autopm_get_interface" },
	{ 0xe339423f, "usb_enable_autosuspend" },
	{ 0x999e8297, "vfree" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0xc0076498, "v4l2_device_register" },
	{ 0x8145062c, "input_event" },
	{ 0xf6288e02, "__init_waitqueue_head" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0xdd0a2ba2, "strlcat" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x92b38c92, "usb_string" },
	{ 0xe13d8c7, "video_device_alloc" },
	{ 0xada71a4a, "usb_deregister" },
	{ 0x48a0f939, "mutex_lock_interruptible" },
	{ 0xdc798d37, "__mutex_init" },
	{ 0x27e1a049, "printk" },
	{ 0x71c90087, "memcmp" },
	{ 0x86078459, "video_unregister_device" },
	{ 0x76674731, "usb_set_interface" },
	{ 0xaafdc258, "strcasecmp" },
	{ 0xc54b5fd9, "usb_control_msg" },
	{ 0x73e20c1c, "strlcpy" },
	{ 0x41e6fc4b, "usb_driver_claim_interface" },
	{ 0xe16b893b, "mutex_lock" },
	{ 0xdc3fcbc9, "__sw_hweight8" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0x52f7f76c, "usb_free_coherent" },
	{ 0x6f081afb, "vm_insert_page" },
	{ 0x5ebefe4b, "v4l_printk_ioctl" },
	{ 0xc7599f6d, "usb_submit_urb" },
	{ 0xbb4f6c53, "kmem_cache_alloc" },
	{ 0xd7e7b078, "usb_get_dev" },
	{ 0x6bf33cf6, "video_devdata" },
	{ 0x6fc6666b, "input_register_device" },
	{ 0xdca94a2b, "usb_put_dev" },
	{ 0x1000e51, "schedule" },
	{ 0x2aa0e4fc, "strncasecmp" },
	{ 0xb4a635bd, "usb_driver_release_interface" },
	{ 0x814a5ecc, "input_free_device" },
	{ 0xa0b04675, "vmalloc_32" },
	{ 0x2b56e3cf, "usb_get_intf" },
	{ 0xefdd5a63, "ktime_get_ts" },
	{ 0xb9e52429, "__wake_up" },
	{ 0x37a0cba, "kfree" },
	{ 0x9d669763, "memcpy" },
	{ 0x105535c7, "input_unregister_device" },
	{ 0x75a17bed, "prepare_to_wait" },
	{ 0xcd89fc0b, "usb_match_one_id" },
	{ 0x72756a48, "usb_register_driver" },
	{ 0x8893fa5d, "finish_wait" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xe8cf19ad, "usb_ifnum_to_if" },
	{ 0x701d0ebd, "snprintf" },
	{ 0xab546925, "vmalloc_to_page" },
	{ 0x199b9b48, "usb_alloc_coherent" },
	{ 0xc3fe87c8, "param_ops_uint" },
	{ 0xec1b4997, "dev_get_drvdata" },
	{ 0x704d893d, "usb_free_urb" },
	{ 0xa2479489, "usb_autopm_put_interface" },
	{ 0x1ee40ce7, "usb_alloc_urb" },
	{ 0xdf401c2b, "usb_put_intf" },
	{ 0x325b93fe, "input_allocate_device" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0458p706Ed*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v045Ep00F8d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v045Ep0723d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v046Dp08C1d*dc*dsc*dp*icFFisc01ip00*");
MODULE_ALIAS("usb:v046Dp08C2d*dc*dsc*dp*icFFisc01ip00*");
MODULE_ALIAS("usb:v046Dp08C3d*dc*dsc*dp*icFFisc01ip00*");
MODULE_ALIAS("usb:v046Dp08C5d*dc*dsc*dp*icFFisc01ip00*");
MODULE_ALIAS("usb:v046Dp08C6d*dc*dsc*dp*icFFisc01ip00*");
MODULE_ALIAS("usb:v046Dp08C7d*dc*dsc*dp*icFFisc01ip00*");
MODULE_ALIAS("usb:v04F2pB071d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v058Fp3820d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v05ACp8501d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v05E3p0505d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v06F8p300Cd*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v0AC8p332Dd*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v0AC8p3410d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v0AC8p3420d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v0E8Dp0004d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v13D3p5103d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v152Dp0310d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v174Fp5212d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v174Fp5931d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v174Fp8A12d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v174Fp8A31d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v174Fp8A33d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v174Fp8A34d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v17DCp0202d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v17EFp480Bd*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v1871p0306d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v18CDpCAFEd*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v18ECp3188d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v18ECp3288d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v18ECp3290d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v19ABp1000d012[0-6]dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v19ABp1000d01[0-1]*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v19ABp1000d00*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v1B3Bp2951d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v1C4Fp3000d*dc*dsc*dp*ic0Eisc01ip00*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic0Eisc01ip00*");

MODULE_INFO(srcversion, "BF09AB69B8595FD839AB561");
