Make: VERTEX.o  DIGRAPH.o  ep.o
	gcc VERTEX.o DIGRAPH.o ep.o -o Make 

ep.o:  ep.c
	gcc -c -Wall -ansi -pedantic ep.c

DIGRAPH.o:  DIGRAPH.c
	gcc -c -Wall -ansi -pedantic DIGRAPH.c

VERTEX.o: VERTEX.c
	gcc -c -Wall -ansi -pedantic VERTEX.c

clean:
	rm -f DIGRAPH.o VERTEX.o ep.o
