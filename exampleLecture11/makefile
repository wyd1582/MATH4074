CC = g++
LD = g++
CFLAGS = -c -O
LIBS = -ldl

PROG_OBJS = readAttributes.o setAttributes.o readSetMain.o

TGTS = readAttributes.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(LFLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o

