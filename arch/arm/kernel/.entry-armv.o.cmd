cmd_arch/arm/kernel/entry-armv.o := /home/ridi/p123/p123/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi-gcc -Wp,-MD,arch/arm/kernel/.entry-armv.o.d  -nostdinc -isystem /home/ridi/p123/p123/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -I/home/ridi/p123/p123/kernel_imx/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-mx6/include -Iarch/arm/plat-mxc/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables  -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float        -c -o arch/arm/kernel/entry-armv.o arch/arm/kernel/entry-armv.S

source_arch/arm/kernel/entry-armv.o := arch/arm/kernel/entry-armv.S

deps_arch/arm/kernel/entry-armv.o := \
    $(wildcard include/config/multi/irq/handler.h) \
    $(wildcard include/config/kprobes.h) \
    $(wildcard include/config/aeabi.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/needs/syscall/for/cmpxchg.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/neon.h) \
    $(wildcard include/config/cpu/arm610.h) \
    $(wildcard include/config/cpu/arm710.h) \
    $(wildcard include/config/iwmmxt.h) \
    $(wildcard include/config/crunch.h) \
    $(wildcard include/config/vfp.h) \
    $(wildcard include/config/cpu/use/domains.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/memory.h \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/arm/patch/phys/virt/16bit.h) \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/const.h \
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
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/arch/mx5.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/sizes.h \
  include/asm-generic/sizes.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
  include/asm-generic/getorder.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/glue-df.h \
    $(wildcard include/config/cpu/abrt/lv4t.h) \
    $(wildcard include/config/cpu/abrt/ev4.h) \
    $(wildcard include/config/cpu/abrt/ev4t.h) \
    $(wildcard include/config/cpu/abrt/ev5tj.h) \
    $(wildcard include/config/cpu/abrt/ev5t.h) \
    $(wildcard include/config/cpu/abrt/ev6.h) \
    $(wildcard include/config/cpu/abrt/ev7.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/glue.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/glue-pf.h \
    $(wildcard include/config/cpu/pabrt/legacy.h) \
    $(wildcard include/config/cpu/pabrt/v6.h) \
    $(wildcard include/config/cpu/pabrt/v7.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/vfpmacros.h \
    $(wildcard include/config/vfpv3.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/hwcap.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/vfp.h \
  arch/arm/plat-mxc/include/mach/entry-macro.S \
    $(wildcard include/config/arm/gic.h) \
    $(wildcard include/config/mxc/tzic.h) \
    $(wildcard include/config/mxc/irq/prior.h) \
  arch/arm/plat-mxc/include/mach/hardware.h \
    $(wildcard include/config/arch/mx2.h) \
  arch/arm/plat-mxc/include/mach/mxc.h \
    $(wildcard include/config/soc/imx6q.h) \
    $(wildcard include/config/soc/imx31.h) \
    $(wildcard include/config/soc/imx35.h) \
    $(wildcard include/config/soc/imx37.h) \
    $(wildcard include/config/soc/imx50.h) \
    $(wildcard include/config/soc/imx51.h) \
    $(wildcard include/config/soc/imx53.h) \
  arch/arm/plat-mxc/include/mach/mx6.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/hardware/entry-macro-gic.S \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/hardware/gic.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/thread_notify.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/unwind.h \
    $(wildcard include/config/arm/unwind.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/unistd.h \
    $(wildcard include/config/oabi/compat.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/tls.h \
    $(wildcard include/config/tls/reg/emul.h) \
    $(wildcard include/config/cpu/v6.h) \
    $(wildcard include/config/cpu/32v6k.h) \
  arch/arm/kernel/entry-header.S \
    $(wildcard include/config/frame/pointer.h) \
    $(wildcard include/config/alignment/trap.h) \
    $(wildcard include/config/have/hw/breakpoint.h) \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
  include/linux/linkage.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/linkage.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/assembler.h \
    $(wildcard include/config/cpu/feroceon.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/ptrace.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/asm-offsets.h \
  include/generated/asm-offsets.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/fpstate.h \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/entry-macro-multi.S \
    $(wildcard include/config/local/timers.h) \

arch/arm/kernel/entry-armv.o: $(deps_arch/arm/kernel/entry-armv.o)

$(deps_arch/arm/kernel/entry-armv.o):
