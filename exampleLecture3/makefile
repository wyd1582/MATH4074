CC = g++
CFLAGS = -c -g -O
LIBS = -ldl 

PROG_OBJS = multiplyFunc1.o multiplyFunc2.o cosineFunc.o lecture3_exampleIfElse.o

TGTS = example.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(LFLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o
