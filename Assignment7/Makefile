CFLAGS = -g -Wall -W -Wshadow -Wuninitialized -O
CC     = g++
LINK   = g++
OFILES = dijkstra.o pqueue.o

test: dijkstra
	chmod u+x dotest
	./dotest

trace: dijkstra
	chmod u+x dotest
	./dotest -t

debug: dijkstra
	gdb ./dijkstra

dijkstra : $(OFILES)
	$(LINK) -o dijkstra $(OFILES) 

pqueue.o: pqueue.cpp pqueue.h
	$(CC) $(CFLAGS) -c pqueue.cpp

dijkstra.o: dijkstra.cpp pqueue.h
	$(CC) $(CFLAGS) -c dijkstra.cpp

clean: 
	rm $(OFILES) dijkstra