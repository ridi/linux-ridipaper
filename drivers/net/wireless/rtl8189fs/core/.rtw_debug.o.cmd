cmd_drivers/net/wireless/rtl8189fs/core/rtw_debug.o := /home/ridi/p123/p123/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi-gcc -Wp,-MD,drivers/net/wireless/rtl8189fs/core/.rtw_debug.o.d  -nostdinc -isystem /home/ridi/p123/p123/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -I/home/ridi/p123/p123/kernel_imx/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-mx6/include -Iarch/arm/plat-mxc/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -marm -fno-dwarf2-cfi-asm -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fomit-frame-pointer -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -O1 -Wno-unused-variable -Wno-unused-value -Wno-unused-label -Wno-unused-parameter -Wno-unused-function -Wno-unused -Idrivers/net/wireless/rtl8189fs/include -Idrivers/net/wireless/rtl8189fs/hal/phydm -Idrivers/net/wireless/rtl8189fs/platform -DCONFIG_RTL8188F -DCONFIG_MP_INCLUDED -DCONFIG_POWER_SAVING -DCONFIG_TRAFFIC_PROTECT -DCONFIG_LOAD_PHY_PARA_FROM_FILE -DREALTEK_CONFIG_PATH=\"\" -DCONFIG_TXPWR_BY_RATE_EN=1 -DCONFIG_TXPWR_LIMIT_EN=1 -DCONFIG_RTW_ADAPTIVITY_EN=1 -DCONFIG_RTW_ADAPTIVITY_MODE=0 -DCONFIG_WOWLAN -DCONFIG_RTW_SDIO_PM_KEEP_POWER -DCONFIG_GPIO_WAKEUP -DHIGH_ACTIVE=0 -DCONFIG_RTW_SDIO_PM_KEEP_POWER -DCONFIG_BR_EXT '-DCONFIG_BR_EXT_BRNAME="'br0'"' -DDM_ODM_SUPPORT_TYPE=0x04 -DCONFIG_LITTLE_ENDIAN -DCONFIG_IOCTL_CFG80211 -DRTW_ENABLE_WIFI_CONTROL_FUNC -DCONFIG_CONCURRENT_MODE  -DMODULE  -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(rtw_debug)"  -D"KBUILD_MODNAME=KBUILD_STR(8189fs)" -c -o drivers/net/wireless/rtl8189fs/core/.tmp_rtw_debug.o drivers/net/wireless/rtl8189fs/core/rtw_debug.c

source_drivers/net/wireless/rtl8189fs/core/rtw_debug.o := drivers/net/wireless/rtl8189fs/core/rtw_debug.c

deps_drivers/net/wireless/rtl8189fs/core/rtw_debug.o := \
    $(wildcard include/config/debug/rtl871x.h) \
    $(wildcard include/config/tdls.h) \
    $(wildcard include/config/ioctl/cfg80211.h) \
    $(wildcard include/config/radio/work.h) \
    $(wildcard include/config/debug.h) \
    $(wildcard include/config/concurrent/mode.h) \
    $(wildcard include/config/power/saving.h) \
    $(wildcard include/config/load/phy/para/from/file.h) \
    $(wildcard include/config/path.h) \
    $(wildcard include/config/multidrv.h) \
    $(wildcard include/config/path/with/ic/name/folder.h) \
    $(wildcard include/config/calibrate/tx/power/by/regulatory.h) \
    $(wildcard include/config/calibrate/tx/power/to/max.h) \
    $(wildcard include/config/txpwr/by/rate/en.h) \
    $(wildcard include/config/txpwr/limit/en.h) \
    $(wildcard include/config/disable/odm.h) \
    $(wildcard include/config/minimal/memory/usage.h) \
    $(wildcard include/config/rtw/adaptivity/en.h) \
    $(wildcard include/config/rtw/adaptivity/mode.h) \
    $(wildcard include/config/wowlan.h) \
    $(wildcard include/config/gpio/wakeup.h) \
    $(wildcard include/config/usb/hci.h) \
    $(wildcard include/config/support/usb/int.h) \
    $(wildcard include/config/usb/interrupt/in/pipe.h) \
    $(wildcard include/config/usb/tx/aggregation.h) \
    $(wildcard include/config/usb/rx/aggregation.h) \
    $(wildcard include/config/use/usb/buffer/alloc/tx.h) \
    $(wildcard include/config/use/usb/buffer/alloc/rx.h) \
    $(wildcard include/config/prealloc/recv/skb.h) \
    $(wildcard include/config/fix/nr/bulkin/buffer.h) \
    $(wildcard include/config/sdio/hci.h) \
    $(wildcard include/config/tx/aggregation.h) \
    $(wildcard include/config/rx/aggregation.h) \
    $(wildcard include/config/pci/hci.h) \
    $(wildcard include/config/rtl8814a.h) \
    $(wildcard include/config/dfs/master.h) \
    $(wildcard include/config/proc/debug.h) \
    $(wildcard include/config/layer2/roaming.h) \
    $(wildcard include/config/80211n/ht.h) \
    $(wildcard include/config/scan/backop.h) \
    $(wildcard include/config/signal/display/dbm.h) \
    $(wildcard include/config/background/noise/monitor.h) \
    $(wildcard include/config/mp/included.h) \
    $(wildcard include/config/80211ac/vht.h) \
    $(wildcard include/config/dbg/counter.h) \
    $(wildcard include/config/ap/mode.h) \
    $(wildcard include/config/prealloc/rx/skb/buffer.h) \
    $(wildcard include/config/find/best/channel.h) \
    $(wildcard include/config/bt/coexist.h) \
    $(wildcard include/config/error/detect.h) \
    $(wildcard include/config/p2p/wowlan.h) \
    $(wildcard include/config/fwlps/in/ips.h) \
    $(wildcard include/config/tdls/ch/sw.h) \
    $(wildcard include/config/ieee80211w.h) \
  drivers/net/wireless/rtl8189fs/include/drv_types.h \
    $(wildcard include/config/arp/keep/alive.h) \
    $(wildcard include/config/intel/widi.h) \
    $(wildcard include/config/beamforming.h) \
    $(wildcard include/config/wapi/support.h) \
    $(wildcard include/config/drvext.h) \
    $(wildcard include/config/br/ext.h) \
    $(wildcard include/config/iol.h) \
    $(wildcard include/config/1t1r.h) \
    $(wildcard include/config/2t2r.h) \
    $(wildcard include/config/rtw/customer/str.h) \
    $(wildcard include/config/tx/early/mode.h) \
    $(wildcard include/config/adaptor/info/caching/file.h) \
    $(wildcard include/config/80211d.h) \
    $(wildcard include/config/special/setting/for/funai/tv.h) \
    $(wildcard include/config/ieee80211/band/5ghz.h) \
    $(wildcard include/config/multi/vir/ifaces.h) \
    $(wildcard include/config/auto/chnl/sel/nhm.h) \
    $(wildcard include/config/gspi/hci.h) \
    $(wildcard include/config/sdio/indirect/access.h) \
    $(wildcard include/config/usb/vendor/req/mutex.h) \
    $(wildcard include/config/usb/vendor/req/buffer/prealloc.h) \
    $(wildcard include/config/intel/proxim.h) \
    $(wildcard include/config/mac/loopback/driver.h) \
    $(wildcard include/config/p2p.h) \
    $(wildcard include/config/wfd.h) \
    $(wildcard include/config/bt/coexist/socket/trx.h) \
    $(wildcard include/config/gpio/api.h) \
    $(wildcard include/config/autosuspend.h) \
    $(wildcard include/config/pno/support.h) \
    $(wildcard include/config/pno/set/debug.h) \
  drivers/net/wireless/rtl8189fs/include/drv_conf.h \
    $(wildcard include/config/android.h) \
    $(wildcard include/config/platform/android.h) \
    $(wildcard include/config/validate/ssid.h) \
    $(wildcard include/config/has/earlysuspend.h) \
    $(wildcard include/config/resume/in/workqueue.h) \
    $(wildcard include/config/android/power.h) \
    $(wildcard include/config/wakelock.h) \
    $(wildcard include/config/vendor/req/retry.h) \
    $(wildcard include/config/rtw/hiq/filter.h) \
    $(wildcard include/config/rtw/adaptivity/dml.h) \
    $(wildcard include/config/rtw/adaptivity/dc/backoff.h) \
    $(wildcard include/config/rtw/adaptivity/th/l2h/ini.h) \
    $(wildcard include/config/rtw/adaptivity/th/edcca/hl/diff.h) \
    $(wildcard include/config/rtw/target/tx/pwr/2g/a.h) \
    $(wildcard include/config/rtw/target/tx/pwr/2g/b.h) \
    $(wildcard include/config/rtw/target/tx/pwr/2g/c.h) \
    $(wildcard include/config/rtw/target/tx/pwr/2g/d.h) \
    $(wildcard include/config/rtw/target/tx/pwr/5g/a.h) \
    $(wildcard include/config/rtw/target/tx/pwr/5g/b.h) \
    $(wildcard include/config/rtw/target/tx/pwr/5g/c.h) \
    $(wildcard include/config/rtw/target/tx/pwr/5g/d.h) \
    $(wildcard include/config/rtw/amplifier/type/2g.h) \
    $(wildcard include/config/rtw/amplifier/type/5g.h) \
    $(wildcard include/config/rtw/rfe/type.h) \
    $(wildcard include/config/rtw/glna/type.h) \
    $(wildcard include/config/rtw/pll/ref/clk/sel.h) \
    $(wildcard include/config/rtl8812a.h) \
    $(wildcard include/config/rtl8821a.h) \
    $(wildcard include/config/deauth/before/connect.h) \
    $(wildcard include/config/wext/dont/join/byssid.h) \
    $(wildcard include/config/doscan/in/busytraffic.h) \
  drivers/net/wireless/rtl8189fs/include/autoconf.h \
    $(wildcard include/config/rtl8188f.h) \
    $(wildcard include/config/recv/reordering/ctrl.h) \
    $(wildcard include/config/platform/intel/byt.h) \
    $(wildcard include/config/cfg80211/force/compatible/2/6/37/under.h) \
    $(wildcard include/config/debug/cfg80211.h) \
    $(wildcard include/config/set/scan/deny/timer.h) \
    $(wildcard include/config/nativeap/mlme.h) \
    $(wildcard include/config/hostapd/mlme.h) \
    $(wildcard include/config/tx/mcast2uni.h) \
    $(wildcard include/config/p2p/remove/group/info.h) \
    $(wildcard include/config/dbg/p2p.h) \
    $(wildcard include/config/p2p/ps.h) \
    $(wildcard include/config/p2p/op/chk/social/ch.h) \
    $(wildcard include/config/cfg80211/onechannel/under/concurrent.h) \
    $(wildcard include/config/p2p/chk/invite/ch/list.h) \
    $(wildcard include/config/p2p/invite/iot.h) \
    $(wildcard include/config/tdls/driver/setup.h) \
    $(wildcard include/config/tdls/autosetup.h) \
    $(wildcard include/config/tdls/autocheckalive.h) \
    $(wildcard include/config/hwport/swap.h) \
    $(wildcard include/config/runtime/port/switch.h) \
    $(wildcard include/config/tsf/reset/offload.h) \
    $(wildcard include/config/layer2/roaming/resume.h) \
    $(wildcard include/config/antenna/diversity.h) \
    $(wildcard include/config/sw/led.h) \
    $(wildcard include/config/xmit/ack.h) \
    $(wildcard include/config/active/keep/alive/check.h) \
    $(wildcard include/config/c2h/packet/en.h) \
    $(wildcard include/config/rf/gain/offset.h) \
    $(wildcard include/config/sdio/chk/hci/resume.h) \
    $(wildcard include/config/sdio/rx/copy.h) \
    $(wildcard include/config/xmit/thread/mode.h) \
    $(wildcard include/config/sdio/tx/enable/aval/int.h) \
    $(wildcard include/config/recv/thread/mode.h) \
    $(wildcard include/config/skb/copy.h) \
    $(wildcard include/config/new/signal/stat/process.h) \
    $(wildcard include/config/embedded/fwimg.h) \
    $(wildcard include/config/file/fwimg.h) \
    $(wildcard include/config/long/delay/issue.h) \
    $(wildcard include/config/patch/join/wrong/channel.h) \
    $(wildcard include/config/attempt/to/fix/ap/beacon/error.h) \
    $(wildcard include/config/mp/iwpriv/support.h) \
    $(wildcard include/config/ips.h) \
    $(wildcard include/config/lps.h) \
    $(wildcard include/config/lps/lclk.h) \
    $(wildcard include/config/check/leave/lps.h) \
    $(wildcard include/config/lps/slow/transition.h) \
    $(wildcard include/config/detect/cpwm/by/polling.h) \
    $(wildcard include/config/lps/rpwm/timer.h) \
    $(wildcard include/config/lps/lclk/wd/timer.h) \
    $(wildcard include/config/ips/check/in/wd.h) \
    $(wildcard include/config/swlps/in/ips.h) \
    $(wildcard include/config/gtk/ol.h) \
    $(wildcard include/config/fw/c2h/debug.h) \
  drivers/net/wireless/rtl8189fs/include/hal_ic_cfg.h \
    $(wildcard include/config/rtl8188e.h) \
    $(wildcard include/config/rtl8192e.h) \
    $(wildcard include/config/rtl8723b.h) \
    $(wildcard include/config/rtl8703b.h) \
    $(wildcard include/config/rtl8822b.h) \
  drivers/net/wireless/rtl8189fs/include/basic_types.h \
  include/linux/version.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/posix_types.h \
  include/linux/module.h \
    $(wildcard include/config/symbol/prefix.h) \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/debug/set/module/ronx.h) \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  include/linux/const.h \
  include/linux/stat.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/stat.h \
  include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/compaction.h) \
  /home/ridi/p123/p123/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include/stdarg.h \
  include/linux/linkage.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/linkage.h \
  include/linux/bitops.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/bitops.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/system.h \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/v6.h) \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  include/linux/typecheck.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/irqflags.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/hwcap.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  include/asm-generic/cmpxchg-local.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/le.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/swab.h \
  include/linux/byteorder/generic.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/printk.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  include/linux/init.h \
    $(wildcard include/config/hotplug.h) \
  include/linux/dynamic_debug.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/div64.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  include/linux/seqlock.h \
  include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  include/linux/stringify.h \
  include/linux/bottom_half.h \
  include/linux/spinlock_types.h \
  include/linux/spinlock_types_up.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
  include/linux/rwlock_types.h \
  include/linux/spinlock_up.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/processor.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/arm/errata/754327.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/hw_breakpoint.h \
  include/linux/rwlock.h \
  include/linux/spinlock_api_up.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/atomic.h \
    $(wildcard include/config/generic/atomic64.h) \
  include/asm-generic/atomic-long.h \
  include/linux/math64.h \
  include/linux/kmod.h \
  include/linux/gfp.h \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
  include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/arch/populates/node/map.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  include/linux/wait.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/current.h \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/linux/nodemask.h \
  include/linux/bitmap.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/string.h \
  include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/generated/bounds.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/glue.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/memory.h \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/arm/patch/phys/virt/16bit.h) \
  arch/arm/plat-mxc/include/mach/memory.h \
    $(wildcard include/config/runtime/phys/offset.h) \
    $(wildcard include/config/arch/mx1.h) \
    $(wildcard include/config/mach/mx21.h) \
    $(wildcard include/config/arch/mx25.h) \
    $(wildcard include/config/mach/mx27.h) \
    $(wildcard include/config/arch/mx3.h) \
    $(wildcard include/config/arch/mx50.h) \
    $(wildcard include/config/arch/mx51.h) \
    $(wildcard include/config/arch/mx53.h) \
    $(wildcard include/config/arch/mx6.h) \
    $(wildcard include/config/mx3/video.h) \
    $(wildcard include/config/mx1/video.h) \
    $(wildcard include/config/video/mx2/hostsupport.h) \
    $(wildcard include/config/arch/mx5.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/sizes.h \
  include/asm-generic/sizes.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  include/asm-generic/getorder.h \
  include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
  include/linux/notifier.h \
  include/linux/errno.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  include/linux/rwsem-spinlock.h \
  include/linux/srcu.h \
  include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
  include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  include/linux/pfn.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/percpu.h \
  include/asm-generic/percpu.h \
  include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/topology.h \
  include/asm-generic/topology.h \
  include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/jiffies.h \
  include/linux/timex.h \
  include/linux/param.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/timex.h \
  arch/arm/plat-mxc/include/mach/timex.h \
    $(wildcard include/config/arch/mx2.h) \
  include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  include/linux/sysctl.h \
  include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tiny/preempt/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/preempt/rt.h) \
  include/linux/completion.h \
  include/linux/rcutree.h \
  include/linux/elf.h \
  include/linux/elf-em.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/elf.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/user.h \
  include/linux/kobject.h \
  include/linux/sysfs.h \
  include/linux/kobject_ns.h \
  include/linux/kref.h \
  include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  include/linux/tracepoint.h \
  include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/module.h \
    $(wildcard include/config/arm/unwind.h) \
  include/trace/events/module.h \
  include/trace/define_trace.h \
  include/linux/utsname.h \
    $(wildcard include/config/uts/ns.h) \
  include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/virt/cpu/accounting.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/generic/hardirqs.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/irq/time/accounting.h) \
    $(wildcard include/config/proc/fs.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/debug/stack/usage.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/mm/owner.h) \
  include/linux/capability.h \
  include/linux/rbtree.h \
  include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/transparent/hugepage.h) \
  include/linux/auxvec.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/auxvec.h \
  include/linux/prio_tree.h \
  include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/mmu.h \
    $(wildcard include/config/cpu/has/asid.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/cputime.h \
  include/asm-generic/cputime.h \
  include/linux/sem.h \
  include/linux/ipc.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/ipcbuf.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/sembuf.h \
  include/linux/signal.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/signal.h \
  include/asm-generic/signal-defs.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/sigcontext.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/siginfo.h \
  include/asm-generic/siginfo.h \
  include/linux/pid.h \
  include/linux/proportions.h \
  include/linux/percpu_counter.h \
  include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
  include/linux/rculist.h \
  include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  include/linux/resource.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/resource.h \
  include/asm-generic/resource.h \
  include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/timerfd.h) \
  include/linux/timerqueue.h \
  include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  include/linux/latencytop.h \
  include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/user/ns.h) \
  include/linux/key.h \
    $(wildcard include/config/sysctl.h) \
  include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  include/linux/aio.h \
  include/linux/aio_abi.h \
  include/linux/uio.h \
  include/linux/nsproxy.h \
  include/linux/err.h \
  drivers/net/wireless/rtl8189fs/include/osdep_service.h \
    $(wildcard include/config/use/vmalloc.h) \
    $(wildcard include/config/ap/wowlan.h) \
  drivers/net/wireless/rtl8189fs/include/osdep_service_linux.h \
    $(wildcard include/config/net/radio.h) \
    $(wildcard include/config/wireless/ext.h) \
    $(wildcard include/config/tcp/csum/offload/tx.h) \
    $(wildcard include/config/efuse/config/file.h) \
    $(wildcard include/config/file.h) \
    $(wildcard include/config/usb/suspend.h) \
  include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/debug/slab.h) \
    $(wildcard include/config/slab.h) \
  include/linux/slab_def.h \
  include/trace/events/kmem.h \
  include/trace/events/gfpflags.h \
  include/linux/kmalloc_sizes.h \
  include/linux/netdevice.h \
    $(wildcard include/config/dcb.h) \
    $(wildcard include/config/wlan.h) \
    $(wildcard include/config/ax25.h) \
    $(wildcard include/config/mac80211/mesh.h) \
    $(wildcard include/config/tr.h) \
    $(wildcard include/config/net/ipip.h) \
    $(wildcard include/config/net/ipgre.h) \
    $(wildcard include/config/ipv6/sit.h) \
    $(wildcard include/config/ipv6/tunnel.h) \
    $(wildcard include/config/netpoll.h) \
    $(wildcard include/config/rps.h) \
    $(wildcard include/config/xps.h) \
    $(wildcard include/config/rfs/accel.h) \
    $(wildcard include/config/net/poll/controller.h) \
    $(wildcard include/config/fcoe.h) \
    $(wildcard include/config/vlan/8021q.h) \
    $(wildcard include/config/net/dsa.h) \
    $(wildcard include/config/net/ns.h) \
    $(wildcard include/config/net/dsa/tag/dsa.h) \
    $(wildcard include/config/net/dsa/tag/trailer.h) \
    $(wildcard include/config/netpoll/trap.h) \
  include/linux/if.h \
  include/linux/socket.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/socket.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/sockios.h \
  include/linux/sockios.h \
  include/linux/hdlc/ioctl.h \
  include/linux/if_ether.h \
  include/linux/skbuff.h \
    $(wildcard include/config/nf/conntrack.h) \
    $(wildcard include/config/bridge/netfilter.h) \
    $(wildcard include/config/nf/defrag/ipv4.h) \
    $(wildcard include/config/nf/defrag/ipv6.h) \
    $(wildcard include/config/xfrm.h) \
    $(wildcard include/config/net/sched.h) \
    $(wildcard include/config/net/cls/act.h) \
    $(wildcard include/config/ipv6/ndisc/nodetype.h) \
    $(wildcard include/config/net/dma.h) \
    $(wildcard include/config/network/secmark.h) \
    $(wildcard include/config/network/phy/timestamping.h) \
  include/linux/kmemcheck.h \
  include/linux/net.h \
  include/linux/random.h \
  include/linux/ioctl.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  include/linux/irqnr.h \
  include/linux/fcntl.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/fcntl.h \
  include/asm-generic/fcntl.h \
  include/linux/textsearch.h \
  include/net/checksum.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/uaccess.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/checksum.h \
  include/linux/in6.h \
  include/linux/dmaengine.h \
    $(wildcard include/config/async/tx/enable/channel/switch.h) \
    $(wildcard include/config/dma/engine.h) \
    $(wildcard include/config/async/tx/dma.h) \
  include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  include/linux/ioport.h \
  include/linux/klist.h \
  include/linux/pm.h \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/pm/runtime.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/device.h \
    $(wildcard include/config/dmabounce.h) \
  include/linux/pm_wakeup.h \
  include/linux/scatterlist.h \
    $(wildcard include/config/debug/sg.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/scatterlist.h \
  include/asm-generic/scatterlist.h \
    $(wildcard include/config/need/sg/dma/length.h) \
  include/linux/mm.h \
    $(wildcard include/config/ksm.h) \
    $(wildcard include/config/debug/pagealloc.h) \
    $(wildcard include/config/hibernation.h) \
    $(wildcard include/config/hugetlbfs.h) \
  include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  include/linux/range.h \
  include/linux/bit_spinlock.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/pgtable.h \
    $(wildcard include/config/highpte.h) \
  include/asm-generic/4level-fixup.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/proc-fns.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/glue-proc.h \
    $(wildcard include/config/cpu/arm610.h) \
    $(wildcard include/config/cpu/arm7tdmi.h) \
    $(wildcard include/config/cpu/arm710.h) \
    $(wildcard include/config/cpu/arm720t.h) \
    $(wildcard include/config/cpu/arm740t.h) \
    $(wildcard include/config/cpu/arm9tdmi.h) \
    $(wildcard include/config/cpu/arm920t.h) \
    $(wildcard include/config/cpu/arm922t.h) \
    $(wildcard include/config/cpu/arm925t.h) \
    $(wildcard include/config/cpu/arm926t.h) \
    $(wildcard include/config/cpu/arm940t.h) \
    $(wildcard include/config/cpu/arm946e.h) \
    $(wildcard include/config/cpu/arm1020.h) \
    $(wildcard include/config/cpu/arm1020e.h) \
    $(wildcard include/config/cpu/arm1022.h) \
    $(wildcard include/config/cpu/arm1026.h) \
    $(wildcard include/config/cpu/mohawk.h) \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/cpu/v6k.h) \
    $(wildcard include/config/cpu/v7.h) \
  arch/arm/plat-mxc/include/mach/vmalloc.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/pgtable-hwdef.h \
  include/asm-generic/pgtable.h \
  include/linux/page-flags.h \
    $(wildcard include/config/pageflags/extended.h) \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/swap.h) \
    $(wildcard include/config/s390.h) \
  include/linux/huge_mm.h \
  include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
  include/linux/vm_event_item.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/io.h \
  arch/arm/plat-mxc/include/mach/io.h \
    $(wildcard include/config/soc/imx31.h) \
    $(wildcard include/config/soc/imx35.h) \
  include/linux/if_packet.h \
  include/linux/if_link.h \
  include/linux/netlink.h \
  include/linux/pm_qos_params.h \
  include/linux/miscdevice.h \
  include/linux/major.h \
  include/linux/delay.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/delay.h \
  include/linux/ethtool.h \
  include/linux/compat.h \
    $(wildcard include/config/nfsd.h) \
    $(wildcard include/config/nfsd/deprecated.h) \
  include/net/net_namespace.h \
    $(wildcard include/config/ipv6.h) \
    $(wildcard include/config/ip/dccp.h) \
    $(wildcard include/config/netfilter.h) \
    $(wildcard include/config/wext/core.h) \
    $(wildcard include/config/net.h) \
  include/net/netns/core.h \
  include/net/netns/mib.h \
    $(wildcard include/config/xfrm/statistics.h) \
  include/net/snmp.h \
  include/linux/snmp.h \
  include/linux/u64_stats_sync.h \
  include/net/netns/unix.h \
  include/net/netns/packet.h \
  include/net/netns/ipv4.h \
    $(wildcard include/config/ip/multiple/tables.h) \
    $(wildcard include/config/ip/mroute.h) \
    $(wildcard include/config/ip/mroute/multiple/tables.h) \
  include/net/inet_frag.h \
  include/net/netns/ipv6.h \
    $(wildcard include/config/ipv6/multiple/tables.h) \
    $(wildcard include/config/ipv6/mroute.h) \
    $(wildcard include/config/ipv6/mroute/multiple/tables.h) \
  include/net/dst_ops.h \
  include/net/netns/dccp.h \
  include/net/netns/x_tables.h \
    $(wildcard include/config/bridge/nf/ebtables.h) \
  include/linux/netfilter.h \
    $(wildcard include/config/netfilter/debug.h) \
    $(wildcard include/config/nf/nat/needed.h) \
  include/linux/in.h \
  include/net/flow.h \
  include/linux/proc_fs.h \
    $(wildcard include/config/proc/devicetree.h) \
    $(wildcard include/config/proc/kcore.h) \
  include/linux/fs.h \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  include/linux/limits.h \
  include/linux/blk_types.h \
    $(wildcard include/config/blk/dev/integrity.h) \
  include/linux/kdev_t.h \
  include/linux/dcache.h \
  include/linux/rculist_bl.h \
  include/linux/list_bl.h \
  include/linux/path.h \
  include/linux/radix-tree.h \
  include/linux/semaphore.h \
  include/linux/fiemap.h \
  include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  include/linux/dqblk_xfs.h \
  include/linux/dqblk_v1.h \
  include/linux/dqblk_v2.h \
  include/linux/dqblk_qtree.h \
  include/linux/nfs_fs_i.h \
  include/linux/nfs.h \
  include/linux/sunrpc/msg_prot.h \
  include/linux/inet.h \
  include/linux/magic.h \
  include/net/netns/conntrack.h \
  include/linux/list_nulls.h \
  include/net/netns/xfrm.h \
  include/linux/xfrm.h \
  include/linux/seq_file_net.h \
  include/linux/seq_file.h \
  include/net/dsa.h \
  include/linux/interrupt.h \
    $(wildcard include/config/irq/forced/threading.h) \
    $(wildcard include/config/generic/irq/probe.h) \
  include/linux/irqreturn.h \
  include/linux/hardirq.h \
  include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/hardirq.h \
    $(wildcard include/config/local/timers.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/irq.h \
  arch/arm/plat-mxc/include/mach/irqs.h \
    $(wildcard include/config/mxc/tzic.h) \
    $(wildcard include/config/arm/gic.h) \
    $(wildcard include/config/soc/imx53.h) \
    $(wildcard include/config/soc/imx50.h) \
    $(wildcard include/config/soc/imx51.h) \
    $(wildcard include/config/mach/mx31ads/wm1133/ev1.h) \
    $(wildcard include/config/mx3/ipu/irqs.h) \
  include/linux/irq_cpustat.h \
  include/trace/events/irq.h \
  include/linux/circ_buf.h \
  include/linux/etherdevice.h \
    $(wildcard include/config/have/efficient/unaligned/access.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/unaligned.h \
  include/linux/unaligned/le_byteshift.h \
  include/linux/unaligned/be_byteshift.h \
  include/linux/unaligned/generic.h \
  include/linux/wireless.h \
  include/net/iw_handler.h \
    $(wildcard include/config/wext/priv.h) \
  include/linux/if_arp.h \
  include/linux/rtnetlink.h \
  include/linux/if_addr.h \
  include/linux/neighbour.h \
  include/linux/ip.h \
  include/linux/kthread.h \
  include/linux/vmalloc.h \
  include/net/ieee80211_radiotap.h \
  include/linux/ieee80211.h \
  include/net/cfg80211.h \
    $(wildcard include/config/nl80211/testmode.h) \
    $(wildcard include/config/cfg80211/wext.h) \
  include/linux/debugfs.h \
    $(wildcard include/config/debug/fs.h) \
  include/linux/nl80211.h \
  include/net/regulatory.h \
  include/linux/earlysuspend.h \
  include/linux/wakelock.h \
    $(wildcard include/config/has/wakelock.h) \
    $(wildcard include/config/wakelock/stat.h) \
  drivers/net/wireless/rtl8189fs/include/rtw_byteorder.h \
    $(wildcard include/config/little/endian.h) \
    $(wildcard include/config/big/endian.h) \
    $(wildcard include/config/platform/mstar389.h) \
  drivers/net/wireless/rtl8189fs/include/byteorder/little_endian.h \
  drivers/net/wireless/rtl8189fs/include/wlan_bssdef.h \
  drivers/net/wireless/rtl8189fs/include/wifi.h \
    $(wildcard include/config/rtl8712fw.h) \
    $(wildcard include/config/error.h) \
    $(wildcard include/config/method/flash.h) \
    $(wildcard include/config/method/ethernet.h) \
    $(wildcard include/config/method/label.h) \
    $(wildcard include/config/method/display.h) \
    $(wildcard include/config/method/e/nfc.h) \
    $(wildcard include/config/method/i/nfc.h) \
    $(wildcard include/config/method/nfc.h) \
    $(wildcard include/config/method/pbc.h) \
    $(wildcard include/config/method/keypad.h) \
    $(wildcard include/config/method/vpbc.h) \
    $(wildcard include/config/method/ppbc.h) \
    $(wildcard include/config/method/vdisplay.h) \
    $(wildcard include/config/method/pdisplay.h) \
  drivers/net/wireless/rtl8189fs/include/ieee80211.h \
    $(wildcard include/config/rtl8711fw.h) \
  include/net/neighbour.h \
  include/net/rtnetlink.h \
  include/net/netlink.h \
  include/net/arp.h \
  drivers/net/wireless/rtl8189fs/include/drv_types_linux.h \
  drivers/net/wireless/rtl8189fs/include/rtw_debug.h \
  drivers/net/wireless/rtl8189fs/include/rtw_rf.h \
    $(wildcard include/config/.h) \
    $(wildcard include/config/1t.h) \
    $(wildcard include/config/2t.h) \
    $(wildcard include/config/1r.h) \
    $(wildcard include/config/2r.h) \
    $(wildcard include/config/1t2r.h) \
    $(wildcard include/config/turbo.h) \
  drivers/net/wireless/rtl8189fs/include/rtw_ht.h \
  drivers/net/wireless/rtl8189fs/include/rtw_cmd.h \
    $(wildcard include/config/event/thread/mode.h) \
    $(wildcard include/config/c2h/wk.h) \
    $(wildcard include/config/h2clbk.h) \
  drivers/net/wireless/rtl8189fs/include/cmd_osdep.h \
  drivers/net/wireless/rtl8189fs/include/rtw_security.h \
  drivers/net/wireless/rtl8189fs/include/rtw_xmit.h \
    $(wildcard include/config/platform/arm/sunxi.h) \
    $(wildcard include/config/platform/arm/sun6i.h) \
    $(wildcard include/config/platform/arm/sun7i.h) \
    $(wildcard include/config/platform/arm/sun8i.h) \
    $(wildcard include/config/platform/arm/sun50iw1p1.h) \
    $(wildcard include/config/platform/mstar.h) \
    $(wildcard include/config/single/xmit/buf.h) \
    $(wildcard include/config/sdio/tx/tasklet.h) \
  drivers/net/wireless/rtl8189fs/include/xmit_osdep.h \
  drivers/net/wireless/rtl8189fs/include/rtw_recv.h \
    $(wildcard include/config/single/recv/buf.h) \
    $(wildcard include/config/tcp/csum/offload/rx.h) \
    $(wildcard include/config/rx/indicate/queue.h) \
    $(wildcard include/config/bsd/rx/use/mbuf.h) \
    $(wildcard include/config/signal/scale/mapping.h) \
  drivers/net/wireless/rtl8189fs/include/recv_osdep.h \
  drivers/net/wireless/rtl8189fs/include/rtw_efuse.h \
  drivers/net/wireless/rtl8189fs/include/rtw_sreset.h \
  drivers/net/wireless/rtl8189fs/include/hal_intf.h \
  drivers/net/wireless/rtl8189fs/include/hal_com.h \
  drivers/net/wireless/rtl8189fs/include/HalVerDef.h \
  drivers/net/wireless/rtl8189fs/include/hal_pg.h \
  drivers/net/wireless/rtl8189fs/include/hal_phy.h \
  drivers/net/wireless/rtl8189fs/include/hal_phy_reg.h \
  drivers/net/wireless/rtl8189fs/include/hal_com_reg.h \
    $(wildcard include/config/usedk.h) \
    $(wildcard include/config/no/usedk.h) \
  drivers/net/wireless/rtl8189fs/include/hal_com_phycfg.h \
  drivers/net/wireless/rtl8189fs/include/../hal/hal_com_c2h.h \
  drivers/net/wireless/rtl8189fs/include/hal_com_h2c.h \
    $(wildcard include/config/ra/dbg/cmd.h) \
  drivers/net/wireless/rtl8189fs/include/hal_com_led.h \
  drivers/net/wireless/rtl8189fs/include/../hal/hal_dm.h \
  drivers/net/wireless/rtl8189fs/include/rtw_qos.h \
  drivers/net/wireless/rtl8189fs/include/rtw_pwrctrl.h \
  drivers/net/wireless/rtl8189fs/include/rtw_mlme.h \
    $(wildcard include/config/dfs.h) \
  drivers/net/wireless/rtl8189fs/include/mlme_osdep.h \
  drivers/net/wireless/rtl8189fs/include/rtw_io.h \
  drivers/net/wireless/rtl8189fs/include/rtw_ioctl.h \
  drivers/net/wireless/rtl8189fs/include/rtw_ioctl_set.h \
  drivers/net/wireless/rtl8189fs/include/rtw_ioctl_query.h \
  drivers/net/wireless/rtl8189fs/include/rtw_ioctl_rtl.h \
  drivers/net/wireless/rtl8189fs/include/osdep_intf.h \
    $(wildcard include/config/r871x/test.h) \
  drivers/net/wireless/rtl8189fs/include/../os_dep/linux/rtw_proc.h \
  drivers/net/wireless/rtl8189fs/include/../os_dep/linux/ioctl_cfg80211.h \
  drivers/net/wireless/rtl8189fs/include/../os_dep/linux/rtw_cfgvendor.h \
  drivers/net/wireless/rtl8189fs/include/rtw_eeprom.h \
  drivers/net/wireless/rtl8189fs/include/sta_info.h \
    $(wildcard include/config/atmel/rc/patch.h) \
    $(wildcard include/config/auto/ap/mode.h) \
  drivers/net/wireless/rtl8189fs/include/rtw_event.h \
  drivers/net/wireless/rtl8189fs/include/rtw_mlme_ext.h \
  drivers/net/wireless/rtl8189fs/include/rtw_ap.h \
  drivers/net/wireless/rtl8189fs/include/rtw_version.h \
  drivers/net/wireless/rtl8189fs/include/rtw_odm.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_types.h \
  drivers/net/wireless/rtl8189fs/include/rtw_p2p.h \
  drivers/net/wireless/rtl8189fs/include/rtw_mp.h \
    $(wildcard include/config/txt.h) \
  drivers/net/wireless/rtl8189fs/include/rtw_br_ext.h \
  drivers/net/wireless/rtl8189fs/include/ip.h \
  drivers/net/wireless/rtl8189fs/include/if_ether.h \
  drivers/net/wireless/rtl8189fs/include/ethernet.h \
  drivers/net/wireless/rtl8189fs/include/circ_buf.h \
  drivers/net/wireless/rtl8189fs/include/rtw_android.h \
  drivers/net/wireless/rtl8189fs/include/drv_types_sdio.h \
    $(wildcard include/config/platform/sprd.h) \
  include/linux/mmc/sdio_func.h \
  include/linux/mod_devicetable.h \
  include/linux/mmc/pm.h \
  include/linux/mmc/sdio_ids.h \
  include/linux/mmc/host.h \
    $(wildcard include/config/mmc/clkgate.h) \
    $(wildcard include/config/mmc/debug.h) \
    $(wildcard include/config/leds/triggers.h) \
    $(wildcard include/config/regulator.h) \
    $(wildcard include/config/mmc/embedded/sdio.h) \
  include/linux/leds.h \
    $(wildcard include/config/leds/trigger/ide/disk.h) \
  include/linux/mmc/core.h \
  include/linux/mmc/card.h \
  drivers/net/wireless/rtl8189fs/include/sdio_osintf.h \
  drivers/net/wireless/rtl8189fs/include/sdio_ops.h \
  drivers/net/wireless/rtl8189fs/include/sdio_ops_linux.h \
  drivers/net/wireless/rtl8189fs/include/sdio_hal.h \
  drivers/net/wireless/rtl8189fs/include/hal_data.h \
    $(wildcard include/config/single/img.h) \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_precomp.h \
    $(wildcard include/config/sfw/supported.h) \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_types.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_features.h \
    $(wildcard include/config/phydm/antenna/diversity.h) \
    $(wildcard include/config/s0s1/sw/antenna/diversity.h) \
    $(wildcard include/config/hl/smart/antenna/type1.h) \
    $(wildcard include/config/path/diversity.h) \
    $(wildcard include/config/ra/dynamic/rty/limit.h) \
    $(wildcard include/config/ant/detection.h) \
    $(wildcard include/config/ra/dynamic/rate/id.h) \
    $(wildcard include/config/rtl/8881a/ant/switch.h) \
    $(wildcard include/config/slot/0/ant/switch.h) \
    $(wildcard include/config/slot/1/ant/switch.h) \
    $(wildcard include/config/no/2g/diversity.h) \
    $(wildcard include/config/2g5g/cg/trx/diversity/8881a.h) \
    $(wildcard include/config/2g/cgcs/rx/diversity.h) \
    $(wildcard include/config/2g/cg/trx/diversity.h) \
    $(wildcard include/config/2g/cg/smart/ant/diversity.h) \
    $(wildcard include/config/no/5g/diversity/8881a.h) \
    $(wildcard include/config/no/5g/diversity.h) \
    $(wildcard include/config/5g/cgcs/rx/diversity/8881a.h) \
    $(wildcard include/config/5g/cgcs/rx/diversity.h) \
    $(wildcard include/config/5g/cg/trx/diversity/8881a.h) \
    $(wildcard include/config/5g/cg/trx/diversity.h) \
    $(wildcard include/config/2g5g/cg/trx/diversity.h) \
    $(wildcard include/config/5g/cg/smart/ant/diversity.h) \
    $(wildcard include/config/not/support/antdiv.h) \
    $(wildcard include/config/2g/support/antdiv.h) \
    $(wildcard include/config/5g/support/antdiv.h) \
    $(wildcard include/config/2g5g/support/antdiv.h) \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm.h \
    $(wildcard include/config/bb/rf.h) \
    $(wildcard include/config/phy/reg/pg/value/type.h) \
    $(wildcard include/config/bb/phy/reg.h) \
    $(wildcard include/config/bb/agc/tab.h) \
    $(wildcard include/config/bb/agc/tab/2g.h) \
    $(wildcard include/config/bb/agc/tab/5g.h) \
    $(wildcard include/config/bb/phy/reg/pg.h) \
    $(wildcard include/config/bb/phy/reg/mp.h) \
    $(wildcard include/config/bb/agc/tab/diff.h) \
    $(wildcard include/config/rf/radio.h) \
    $(wildcard include/config/rf/txpwr/lmt.h) \
    $(wildcard include/config/fw/nic.h) \
    $(wildcard include/config/fw/nic/2.h) \
    $(wildcard include/config/fw/ap.h) \
    $(wildcard include/config/fw/ap/2.h) \
    $(wildcard include/config/fw/mp.h) \
    $(wildcard include/config/fw/wowlan.h) \
    $(wildcard include/config/fw/wowlan/2.h) \
    $(wildcard include/config/fw/ap/wowlan.h) \
    $(wildcard include/config/fw/bt.h) \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_pre_define.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_dig.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_edcaturbocheck.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_pathdiv.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_antdiv.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_antdect.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_dynamicbbpowersaving.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_rainfo.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_dynamictxpower.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_cfotracking.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_acs.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_adaptivity.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_beamforming.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/txbf/halcomtxbf.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/txbf/haltxbfjaguar.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/txbf/haltxbf8192e.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/txbf/haltxbf8814a.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/txbf/haltxbf8821b.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/txbf/haltxbf8822b.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/txbf/haltxbfinterface.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_noisemonitor.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/halphyrf_ce.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_powertracking_ce.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_hwconfig.h \
    $(wildcard include/config/mp.h) \
    $(wildcard include/config/tc.h) \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_debug.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_regdefine11ac.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_regdefine11n.h \
    $(wildcard include/config/anta/11n.h) \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_interface.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/phydm_reg.h \
    $(wildcard include/config/wlan/hal/8814ae.h) \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/rtl8188f/halhwimg8188f_mac.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/rtl8188f/halhwimg8188f_rf.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/rtl8188f/halhwimg8188f_bb.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/rtl8188f/halhwimg8188f_fw.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/rtl8188f/hal8188freg.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/rtl8188f/phydm_rtl8188f.h \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/rtl8188f/phydm_regconfig8188f.h \
    $(wildcard include/config/h/8188f.h) \
  drivers/net/wireless/rtl8189fs/include/../hal/phydm/rtl8188f/halphyrf_8188f.h \
  drivers/net/wireless/rtl8189fs/include/rtl8188f_hal.h \
    $(wildcard include/config/check/bt/hang.h) \
  drivers/net/wireless/rtl8189fs/include/hal_data.h \
  drivers/net/wireless/rtl8189fs/include/rtl8188f_spec.h \
  drivers/net/wireless/rtl8189fs/include/rtl8188f_rf.h \
  drivers/net/wireless/rtl8189fs/include/rtl8188f_dm.h \
  drivers/net/wireless/rtl8189fs/include/rtl8188f_recv.h \
    $(wildcard include/config/platform/hisilicon.h) \
  drivers/net/wireless/rtl8189fs/include/rtl8188f_xmit.h \
  drivers/net/wireless/rtl8189fs/include/rtl8188f_cmd.h \
  drivers/net/wireless/rtl8189fs/include/rtl8188f_led.h \
  drivers/net/wireless/rtl8189fs/include/Hal8188FPwrSeq.h \
  drivers/net/wireless/rtl8189fs/include/HalPwrSeqCmd.h \
  drivers/net/wireless/rtl8189fs/include/Hal8188FPhyReg.h \
  drivers/net/wireless/rtl8189fs/include/Hal8188FPhyCfg.h \
  drivers/net/wireless/rtl8189fs/include/rtl8188f_sreset.h \
  drivers/net/wireless/rtl8189fs/include/hal_com.h \
  drivers/net/wireless/rtl8189fs/include/hal_sdio.h \

drivers/net/wireless/rtl8189fs/core/rtw_debug.o: $(deps_drivers/net/wireless/rtl8189fs/core/rtw_debug.o)

$(deps_drivers/net/wireless/rtl8189fs/core/rtw_debug.o):
