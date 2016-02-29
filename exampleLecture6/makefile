CC = g++
LD = g++
CFLAGS = -c -g -O
LIBS = -ldl

PROG_OBJS = myFunc1.o myFunc2.o lecture6_exampleDataStructure1.o

TGTS = example.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(LFLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o
