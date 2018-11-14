cmd_arch/arm/boot/compressed/piggy.gzip.o := /home/ridi/p123/p123/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi-gcc -Wp,-MD,arch/arm/boot/compressed/.piggy.gzip.o.d  -nostdinc -isystem /home/ridi/p123/p123/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -I/home/ridi/p123/p123/kernel_imx/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-mx6/include -Iarch/arm/plat-mxc/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables  -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float    -Wa,-march=all     -c -o arch/arm/boot/compressed/piggy.gzip.o arch/arm/boot/compressed/piggy.gzip.S

source_arch/arm/boot/compressed/piggy.gzip.o := arch/arm/boot/compressed/piggy.gzip.S

deps_arch/arm/boot/compressed/piggy.gzip.o := \
  /home/ridi/p123/p123/kernel_imx/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \

arch/arm/boot/compressed/piggy.gzip.o: $(deps_arch/arm/boot/compressed/piggy.gzip.o)

$(deps_arch/arm/boot/compressed/piggy.gzip.o):
