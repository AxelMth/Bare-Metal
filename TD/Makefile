PREFIX = arm-none-eabi
CC := $(PREFIX)-gcc
AS := $(PREFIX)-as

ASFLAGS = -g -mcpu=cortex-m0plus
CFLAGS = -g -O1 -mcpu=cortex-m0plus -mthumb -Werror -Wall -Wextra -std=gnu99
SOURCES = uart.c init.c main.c led.c irq.c buttons.c
OBJETS = main.o crt0.o init.o led.o uart.o matrix.o image.o irq.o flash.o buttons.o
CLOCKS = clocks.o 
SOURCES = main.c led.c matrix.c
EXE = main
LFLAGS = -nostdlib -T
LSCRIPT = ld_ram.lds
GDB = arm-none-eabi-gdb

all: $(EXE)

image.o: image.raw
	$(PREFIX)-objcopy -I binary -O elf32-littlearm -B arm $^ $@

$(EXE): $(OBJETS)
	$(CC) $(LFLAGS) $(LSCRIPT) $(OBJETS) $(CLOCKS) -o $(EXE)

startgdbserver:
	 JLinkGDBServer -if swd -device "MKL46Z256xxx4" -LocalhostOnly

-include $(subst .c,.d,$(SOURCES))

%.d : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -MM -MF $@ -MP $<

clean:
	rm -f $(EXE) $(OBJETS) *.d
