CC = g++
LD = g++
#CFLAGS = -c -g -ggdb -O 
#FLAGS = -Wall -pedantic
FLAGS =-g -ggdb -Wall -pedantic -O
LIBS = -ldl

PROG_OBJS = expint.cpp tridiagSolver.cpp CS2_2.cpp

TGTS = prog.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(FLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o
