CC = arm-none-eabi-gcc
CFLAGS = -Wall -Werror -g -O2 -mthumb
FLAGS = -g -O2 -mthumb
LDLIBS = -lm
LDFLAGS = -L/opt/mylibs -mthumb
OBJS = t1.o t2.o main.o stubs.o
EXE = hello

stubs.o : libs/stubs.c  
		$(CC) $(FLAGS) -c -o $@ $< 

$(EXE) : $(OBJS) 
		$(LINK.o) $^ $(LDLIBS) -o $@

.PHONY: clean 
clean :	
	rm -f *.o $(EXE)

