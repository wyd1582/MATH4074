CC = g++
LD = g++
#CFLAGS = -c -g -ggdb -O 
#FLAGS = -Wall -pedantic
FLAGS =-g -ggdb -Wall -pedantic -O
LIBS = -ldl
BIN = ../bin

PROG_OBJS = CS4submit.cpp CS4.cpp FFT.cpp FFT_calculate.cpp FFT_get_twiddle_factors.cpp IFFT.cpp

TGTS = CS4.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(FLAGS) $(PROG_OBJS) $(LIBS) -o $(BIN)/$(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(BIN)/$(TGTS)
	rm -f $(BIN)/*.o

