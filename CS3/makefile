CC = g++
LD = g++
#CFLAGS = -c -g -ggdb -O 
#FLAGS = -Wall -pedantic
FLAGS =-g -ggdb -Wall -pedantic -O
LIBS = -ldl

PROG_OBJS = gamrand.cpp invNormal.cpp ran2_mod.cpp cs3.cpp
PROG_OBJS_ARGS = gamrand.cpp invNormal.cpp ran2_mod.cpp cs3args.cpp

TGTS = CS3.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(FLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)

args:$(PROG_OBJS)
	$(CC) $(FLAGS) $(PROG_OBJS_ARGS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o
