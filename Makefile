
AS=arm-none-eabi-as
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJDUMP=arm-none-eabi-objdump
OBJCOPY=arm-none-eabi-objcopy
SIZE=arm-none-eabi-size

hello_arm.elf: startup.s main.c stm32.ld
	$(AS) -g3 -mcpu=cortex-m0plus -mthumb startup.s -o startup.o -a > startup.lst
	$(CC) -g3 -O0 -c -mcpu=cortex-m0plus -mthumb -Wall -Qn -nostdlib -fomit-frame-pointer --specs=nosys.specs main.c -o main.o
	$(LD) -T stm32.ld startup.o main.o -o hello_arm.elf
