#Makefile used
INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS) -Wall -Werror
LIBS= -lrt

HFILES= 

CFILES= 

OFILES= check_heap.o
SRCS= ${HFILES} ${CFILES}


	
all:	check_heap

clean:
	-rm -f *.o *.d 
	-rm -f pes1 parser

distclean:
	-rm -f *.o *.d


check_heap: $(OFILES)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^


%.o:%.c
	$(CC) $(CFLAGS) -c $<

.cpp.o:
	$(CC) $(CFLAGS) -c $<



