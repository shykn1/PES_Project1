#Makefile used
INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS) 
LIBS= -lrt

HFILES= 

CFILES= pes1.c  parser.c

SRCS= ${HFILES} ${CFILES}


all:	pes1

clean:
	-rm -f *.o *.d 
	-rm -f pes1 parser

distclean:
	-rm -f *.o *.d

pes1: pes1.o parser.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^


%.c:%.o
	$(CC) $(CFLAGS) -c $<

.cpp.o:
	$(CC) $(CFLAGS) -c $<
