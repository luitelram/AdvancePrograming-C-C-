all: assign103
	
assign103: binheap.o assign103.o
	gcc -o assign103 assign103.o binheap.o

binheap.o: binheap.c binheap.h
	gcc -ggdb -Wall -c binheap.c

assign103.o:
	gcc -ggdb -Wall -c assign103.c

clean:
	rm -f assign103 *~ *.o 




