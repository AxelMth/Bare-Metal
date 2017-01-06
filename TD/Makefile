CC = arm-none-eabi-gcc
CFLAGS = -c -g -O1 -mcpu=cortex-m0plus -mthumb 
SOURCES = main.c
OBJETS = ${SOURCES:%c=%o}
LFLAGS = -nostdlib -T
LSCRIPT = ld_ram.lds
EXE = main

GDB = arm-none-eabi-gdb
DRIVER = JLinkGDBServer 
DRIVER_FLAGS = -if swd -device 
GDB_FILE = .gdbinit
DEVICE = "MKL46Z256xxx4"
HOST_O = -LocalhostOnly

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(OBJETS)
	$(CC) $(LFLAGS) $(LSCRIPT) $(OBJETS) -o $(EXE) 

gdb:
	$(DRIVER) $(DRIVER_FLAGS) $(DEVICE) $(HOST_O) 

clean:
	rm -f $(EXE) $(OBJETS)
	
	

