
CC=gcc
CFLAGS:=-std=c99
LDFLAGS=
EXEC=main

all: $(EXEC)

main: clause.o SAT.o vars.o graphe.o queue.o main.o
	$(CC) $(CFLAGS) -o main graphe.o clause.o SAT.o vars.o queue.o main.o $(LDFLAGS)

clause.o: clause.h clause.c
	$(CC) $(CFLAGS) -o clause.o -c clause.c

SAT.o: clause.h SAT.h SAT.c
	$(CC) $(CFLAGS) -o SAT.o -c SAT.c

graphe.o: graphe.c all.h
	$(CC) $(CFLAGS) -o graphe.o -c graphe.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -o queue.o -c queue.c

main.o: clause.h SAT.h all.h vars.h queue.h main.c
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -rf *.o $(EXEC)

mrproper: clean
	rm -rf $(EXEC)
