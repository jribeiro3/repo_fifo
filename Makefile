CC = g++
CXXFLAGS = -Wall -ggdb -pthread

LDFLAGS = -pthread -lm

TARGETS = fifo main

all:	$(TARGETS)

$(TARGETS):	fifo.o main.o
		gcc -o $@ $^ $(LDFLAGS)

$(TARGETS): fifo.h

clean:
		rm -f *.o *~

cleanall:	clean
		rm -f $(TARGETS)
