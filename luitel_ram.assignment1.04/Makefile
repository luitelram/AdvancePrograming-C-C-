all: assign104

assign104: binheap.o assign104.o character.o
	gcc -o assign104 binheap.o assign104.o character.o
binheap.o: binheap.c binheap.h
	gcc -ggdb -Wall -c binheap.c
assign104.o: assign104.c assign104.h
	gcc -ggdb -Wall -c assign104.c
character.o: character.c character.h
	gcc -ggdb -Wall -c character.c
clean:
	rm -f assign104 *~ *.o
