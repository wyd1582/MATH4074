CC = g++
LD = g++
CFLAGS = -c -g -O
LIBS = -ldl 

PROG_OBJS = example1.o

TGTS = exampleExe

$(TGTS):$(PROG_OBJS)
	$(CC) $(LFLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o
