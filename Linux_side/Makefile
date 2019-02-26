#Makefile used
INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS) 
LIBS= -lrt

HFILES= 

CFILES= pes1.c  parser.c
#OFILES= pes1.o  parser.o terminal.o
OFILES= pes1.o   terminal.o allocate.o parser.o free_mem.o display.o common.o write_mem.o invert.o
SRCS= ${HFILES} ${CFILES}


	
all:	pes1

clean:
	-rm -f *.o *.d 
	-rm -f pes1 parser

distclean:
	-rm -f *.o *.d

#pes1: pes1.o parser.o
pes1: $(OFILES)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^


%.o:%.c
	$(CC) $(CFLAGS) -c $<

.cpp.o:
	$(CC) $(CFLAGS) -c $<


test: ./pes1 testscript
	./pes1 < testscript