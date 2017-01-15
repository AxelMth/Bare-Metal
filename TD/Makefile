PREFIX = arm-none-eabi
CC := $(PREFIX)-gcc
AS := $(PREFIX)-as

ASFLAGS = -g -mcpu=cortex-m0plus
CFLAGS = -g -O1 -mcpu=cortex-m0plus -mthumb -Werror -Wall -Wextra
SOURCES = uart.c init.c main.c led.c
OBJETS = main.o crt0.o init.o led.o uart.o
CLOCKS = clocks.o
SOURCES = main.c led.c
EXE = main
LFLAGS = -nostdlib -T
LSCRIPT = ld_ram.lds
GDB = arm-none-eabi-gdb

DRIVER = JLinkGDBServer 
DRIVER_FLAGS = -if swd -device 
GDB_FILE = .gdbinit
DEVICE = "MKL46Z256xxx4"
HOST_O = -LocalhostOnly

all: $(EXE)

$(EXE): $(OBJETS)
	$(CC) $(LFLAGS) $(LSCRIPT) $(OBJETS) $(CLOCKS) -o $(EXE)

startgdbserver:
	$(DRIVER) $(DRIVER_FLAGS) $(DEVICE) $(HOST_O) 

-include $(subst .c,.d,$(SOURCES))

%.d : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -MM -MF $@ -MP $<

clean:
	rm -f $(EXE) $(OBJETS) *.d
