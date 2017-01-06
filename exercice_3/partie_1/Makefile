CC = sh4-unknown-linux-gnu-gcc
EXE = test
SOURCES = test.c
OBJECTS = test.o
OBJDUMP = sh4-unknown-linux-gnu-objdump

$(EXE):
	$(CC) $(SOURCES) -o $(OBJECTS)
	$(CC) $(SOURCES) -o $@  

objdump_h:
	$(OBJDUMP) -h $(OBJECTS) | grep ".rodata"
	$(OBJDUMP) -h $(EXE) | grep ".rodata"

objdump_s:
	$(OBJDUMP) -s --section=.rodata $(OBJECTS)
	$(OBJDUMP) -s --section=.rodata $(EXE)

clean:
	rm -f $(EXE) $(OBJECTS)
