GDB = arm-none-eabi-gdb
DRIVER = JLinkGDBServer 
DRIVER_FLAGS = -if swd -device 
GDB_FILE = .gdbinit
DEVICE = "MLK46Z256VLH4"
HOST_O = -LocalhostOnly

all:
	$(DRIVER) $(DRIVER_FLAGS) $(DEVICE) $(HOST_O) 
	$(GDB) $(GDB_FILE) 
	

