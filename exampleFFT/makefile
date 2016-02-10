CC = g++
LD = g++
CFLAGS = -c -g -O
LIBS = -ldl 

PROG_OBJS = exampleFFT.o FFT.o IFFT.o FFT_calculate.o FFT_get_twiddle_factors.o

TGTS = exampleFFT.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(LFLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o
