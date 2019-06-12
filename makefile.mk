CC=gcc

SRCDIR=./src/
OBJDIR=./obj/

all: maingsl

clean:
	rm -f ./gslspringdata

maingsl: fileobj
	$(CC) -o gslspringdata $(OBJDIR)gslspringdata.o -lgsl -lgslcblas -lm
	rm -f  ./obj/*.o

fileobj:  
	$(CC) -c -o $(OBJDIR)gslspringdata.o $(SRCDIR)gslspringdata.c
	
