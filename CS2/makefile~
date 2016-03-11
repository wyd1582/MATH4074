CC = g++
LD = g++
CFLAGS = -c -g -O 
FLAGS = -Wall -pedantic
LIBS = -ldl

PROG_OBJS = expint.cpp tridiagSolver.cpp CS2_tk2663.cpp

TGTS = prog.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(FLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o
