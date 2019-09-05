CC=gcc
CFLAGS=-Wall -g       # options de compilations
LDFLAGS=              # options de l'éditions de liens

exe: main.o
	$(CC) -o exe main.o $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

clean:
	rm -rf *.o exe