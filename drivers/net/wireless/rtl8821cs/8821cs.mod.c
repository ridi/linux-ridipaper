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
	{ 0x89177421, "wake_lock_destroy" },
	{ 0x55b74b46, "wake_unlock" },
	{ 0xbbe3fb1d, "neigh_lookup" },
	{ 0x975f5a98, "wiphy_unregister" },
	{ 0xc2e42e36, "cfg80211_remain_on_channel_expired" },
	{ 0xe946936, "seq_release" },
	{ 0x43868c44, "sdio_claim_host" },
	{ 0xe914e41e, "strcpy" },
	{ 0xdb7bdd34, "flush_signals" },
	{ 0xdc43a9c8, "daemonize" },
	{ 0x991320ca, "napi_gro_receive" },
	{ 0xe00e14f6, "neigh_destroy" },
	{ 0x74c86cc0, "init_timer_key" },
	{ 0x9653ca8e, "skb_queue_tail" },
	{ 0xf28cce8c, "wake_up_process" },
	{ 0xb58613c3, "sdio_register_driver" },
	{ 0xc3a67c4a, "sock_release" },
	{ 0xc3fe87c8, "param_ops_uint" },
	{ 0x2196324, "__aeabi_idiv" },
	{ 0xb921cbaf, "filp_open" },
	{ 0xde9c0521, "register_netdev" },
	{ 0x72aa82c6, "param_ops_charp" },
	{ 0x349cba85, "strchr" },
	{ 0xa21d2fcd, "unregister_netdev" },
	{ 0x9a1dfd65, "strpbrk" },
	{ 0xd7779230, "cfg80211_put_bss" },
	{ 0xd0d641fc, "platform_driver_register" },
	{ 0x19a38cf5, "arp_tbl" },
	{ 0x82072614, "tasklet_kill" },
	{ 0x56c7f382, "filp_close" },
	{ 0x37a0cba, "kfree" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xd84a0d24, "cfg80211_ibss_joined" },
	{ 0x1f8be0e2, "ntx_wifi_power_ctrl" },
	{ 0x6cd89070, "__netif_schedule" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x1e6d26a8, "strstr" },
	{ 0x67f626e, "cfg80211_michael_mic_failure" },
	{ 0xa170bbdb, "outer_cache" },
	{ 0x8d522714, "__rcu_read_lock" },
	{ 0x59a3e7dc, "skb_dequeue" },
	{ 0x87053831, "cfg80211_get_bss" },
	{ 0x4e830a3e, "strnicmp" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x20000329, "simple_strtoul" },
	{ 0x70b54dd, "unregister_netdevice_queue" },
	{ 0xf9a482f9, "msleep" },
	{ 0x59e5070d, "__do_div64" },
	{ 0x53b2659, "cfg80211_scan_done" },
	{ 0x3a66f264, "cfg80211_send_rx_assoc" },
	{ 0x2469810f, "__rcu_read_unlock" },
	{ 0xff178f6, "__aeabi_idivmod" },
	{ 0x26421558, "napi_complete" },
	{ 0x93fca811, "__get_free_pages" },
	{ 0xd8f795ca, "del_timer" },
	{ 0xec1b4997, "dev_get_drvdata" },
	{ 0xdc5c22a5, "kthread_stop" },
	{ 0x170ec140, "seq_printf" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0x47b3dc0, "unregister_early_suspend" },
	{ 0x57a6504e, "vsnprintf" },
	{ 0x71c90087, "memcmp" },
	{ 0xf47a87d0, "alloc_etherdev_mqs" },
	{ 0xd09824c1, "wiphy_free" },
	{ 0x394e9317, "kill_pid" },
	{ 0x799aca4, "local_bh_enable" },
	{ 0xc9eac8ee, "skb_clone" },
	{ 0x4205ad24, "cancel_work_sync" },
	{ 0xd3a17cd2, "kthread_create_on_node" },
	{ 0xa83dfe6b, "dev_set_drvdata" },
	{ 0xc4463457, "skb_copy_bits" },
	{ 0x9d51d0e0, "sdio_set_block_size" },
	{ 0xae09bbef, "sdio_writeb" },
	{ 0xe627d951, "pskb_copy" },
	{ 0xbe593ae9, "wiphy_apply_custom_regulatory" },
	{ 0x83ce82eb, "get_monotonic_boottime" },
	{ 0x5f754e5a, "memset" },
	{ 0x11089ac7, "_ctype" },
	{ 0xc27487dd, "__bug" },
	{ 0xb0bb9c02, "down_interruptible" },
	{ 0x9448afec, "dev_kfree_skb_any" },
	{ 0x938a4702, "netif_rx" },
	{ 0x46ac9b8, "cfg80211_mgmt_tx_status" },
	{ 0x5baaba0, "wait_for_completion" },
	{ 0x47836ef5, "dev_get_by_name" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0x6fbc0837, "dev_alloc_name" },
	{ 0xf63e4559, "skb_copy" },
	{ 0xe113bbbc, "csum_partial" },
	{ 0x7ab61531, "sdio_f0_readb" },
	{ 0xd79b5a02, "allow_signal" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x328a05f1, "strncpy" },
	{ 0x9e7d6bd0, "__udelay" },
	{ 0x42224298, "sscanf" },
	{ 0x7905e256, "__alloc_skb" },
	{ 0x71d14b87, "netif_carrier_on" },
	{ 0xce2840e7, "irq_set_irq_wake" },
	{ 0x9545af6d, "tasklet_init" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x3ff62317, "local_bh_disable" },
	{ 0x8cf51d15, "up" },
	{ 0x3ec8886f, "param_ops_int" },
	{ 0xfe17fc6d, "sock_create" },
	{ 0x9c64fbd, "ieee80211_frequency_to_channel" },
	{ 0xe2505802, "sdio_memcpy_toio" },
	{ 0xf59f197, "param_array_ops" },
	{ 0x999e8297, "vfree" },
	{ 0x1d54ff52, "netif_device_attach" },
	{ 0x2b688622, "complete_and_exit" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x4059792f, "print_hex_dump" },
	{ 0xc8976ff5, "cfg80211_unlink_bss" },
	{ 0x12f06f15, "platform_get_resource_byname" },
	{ 0xf0ed84dc, "cfg80211_rx_mgmt" },
	{ 0x9079837c, "sdio_release_host" },
	{ 0x65d6d0f0, "gpio_direction_input" },
	{ 0xe8499634, "sock_recvmsg" },
	{ 0xd2965f6f, "kthread_should_stop" },
	{ 0xc95e529d, "seq_open" },
	{ 0x60f71cfa, "complete" },
	{ 0x8662fa87, "wiphy_new" },
	{ 0xe933da0c, "cfg80211_inform_bss_frame" },
	{ 0x176156dd, "down_timeout" },
	{ 0xa7995a54, "cfg80211_connect_result" },
	{ 0xf7802486, "__aeabi_uidivmod" },
	{ 0x85df9b6c, "strsep" },
	{ 0x99bb8806, "memmove" },
	{ 0x533a1419, "find_vpid" },
	{ 0x603b9489, "__napi_schedule" },
	{ 0xec6e1927, "init_net" },
	{ 0xd4e5d889, "skb_put" },
	{ 0x50740360, "seq_lseek" },
	{ 0xf6288e02, "__init_waitqueue_head" },
	{ 0x80d817ab, "wait_for_completion_timeout" },
	{ 0x9a6221c5, "mod_timer" },
	{ 0xe1e9f3ee, "netif_carrier_off" },
	{ 0xa90385c7, "proc_create_data" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0x44e3972b, "cfg80211_disconnected" },
	{ 0x3ecc6f8c, "dev_err" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0x731df3ba, "sdio_memcpy_fromio" },
	{ 0xde5d1761, "wake_lock_init" },
	{ 0x7d11c268, "jiffies" },
	{ 0x1099dee3, "single_release" },
	{ 0xdc7eb4c7, "wiphy_register" },
	{ 0x686d7e95, "sdio_disable_func" },
	{ 0x701d0ebd, "snprintf" },
	{ 0x1f93b044, "cfg80211_roamed" },
	{ 0xb86e4ab9, "random32" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x98259596, "sdio_claim_irq" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x81095488, "register_netdevice" },
	{ 0x97255bdf, "strlen" },
	{ 0x368d7654, "sdio_unregister_driver" },
	{ 0xdc798d37, "__mutex_init" },
	{ 0x4b5cfc8, "sdio_release_irq" },
	{ 0x85670f1d, "rtnl_is_locked" },
	{ 0xf045cd70, "wake_lock_timeout" },
	{ 0xa1638dda, "__pskb_pull_tail" },
	{ 0x12a38747, "usleep_range" },
	{ 0x286c78d1, "free_netdev" },
	{ 0x4bd77304, "sdio_set_host_pm_flags" },
	{ 0x8c042919, "skb_push" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x44da5d0f, "__csum_ipv6_magic" },
	{ 0x2c13bbd7, "remove_proc_entry" },
	{ 0x84b183ae, "strncmp" },
	{ 0x9f984513, "strrchr" },
	{ 0xd61f6b1e, "netif_napi_del" },
	{ 0xa7f1921a, "seq_read" },
	{ 0x17bb3a6f, "skb_trim" },
	{ 0xd07fd4d0, "dev_get_by_index" },
	{ 0x81073680, "sdio_writesb" },
	{ 0x508ca718, "__ieee80211_get_channel" },
	{ 0x1a6076a4, "netif_receive_skb" },
	{ 0xdda9e423, "wake_lock" },
	{ 0x63ecad53, "register_netdevice_notifier" },
	{ 0xfe769456, "unregister_netdevice_notifier" },
	{ 0x3900e0d5, "platform_driver_unregister" },
	{ 0x79581ed4, "sdio_f0_writeb" },
	{ 0x3155d442, "sock_sendmsg" },
	{ 0x9d669763, "memcpy" },
	{ 0x48a0f939, "mutex_lock_interruptible" },
	{ 0xfaef0ed, "__tasklet_schedule" },
	{ 0x5f0c823b, "skb_pull" },
	{ 0x760a0f4f, "yield" },
	{ 0xa628650, "sdio_enable_func" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x806e70ca, "cfg80211_ready_on_channel" },
	{ 0x4b140039, "eth_type_trans" },
	{ 0x62b72b0d, "mutex_unlock" },
	{ 0xd2ccc93d, "sdio_get_host_pm_caps" },
	{ 0xac80c8c1, "sdio_readb" },
	{ 0xa84b1ec6, "proc_mkdir" },
	{ 0x27e1a049, "printk" },
	{ 0x6942a1cc, "sdio_readsb" },
	{ 0x56ea199b, "single_open" },
	{ 0x37befc70, "jiffies_to_msecs" },
	{ 0x8949858b, "schedule_work" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x4302d0eb, "free_pages" },
	{ 0x718d7d73, "cfg80211_send_disassoc" },
	{ 0x8f4641c7, "register_early_suspend" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x6ab418fb, "netif_napi_add" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("sdio:c*v024CdB821*");
MODULE_ALIAS("sdio:c*v024CdC821*");
MODULE_ALIAS("sdio:c07v*d*");

MODULE_INFO(srcversion, "365A7A270B855D6C7906557");
