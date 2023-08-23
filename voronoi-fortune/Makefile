
tt: voronoi t
	./voronoi -t <t >tt
	head tt

voronoi: edgelist.o geometry.o heap.o main.o memory.o output.o voronoi.o
	cc -o voronoi edgelist.o geometry.o heap.o main.o memory.o output.o voronoi.o -lm

edgelist.o:  defs.h edgelist.c
	cc -Wall -c -g edgelist.c

geometry.o:  defs.h geometry.c
	cc -Wall -c -g geometry.c

heap.o:  defs.h heap.c
	cc -Wall -c -g heap.c

main.o:  defs.h main.c
	cc -Wall -c -g main.c

memory.o:  defs.h memory.c
	cc -Wall -c -g memory.c

output.o:  defs.h output.c
	cc -Wall -c -g output.c

voronoi.o: defs.h voronoi.c
	cc -Wall -c -g voronoi.c

clean:
	rm *.o *~ ./voronoi tt
