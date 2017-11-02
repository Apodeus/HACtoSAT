
CC=gcc
CFLAGS:=-std=c99
LDFLAGS=
EXEC=main

all: $(EXEC)

main: clause.o SAT.o test.o util.o main.o
	$(CC) $(CFLAGS) -o main test.o clause.o SAT.o util.o main.o $(LDFLAGS)

clause.o: clause.h clause.c
	$(CC) $(CFLAGS) -o clause.o -c clause.c

SAT.o: clause.h SAT.h SAT.c
	$(CC) $(CFLAGS) -o SAT.o -c SAT.c

test.o: test.c test.h
	$(CC) $(CFLAGS) -o test.o -c test.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -o util.o -c util.c

main.o: clause.h SAT.h test.h util.h main.c
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -rf *.o $(EXEC)

mrproper: clean
	rm -rf $(EXEC)
