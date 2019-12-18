SRC=../src/
HEADERS=$(SRC)*.h

CC=gcc
CFLAGS=-Wall -g       # options de compilations
LDFLAGS=              # options de l'éditions de liens


exe: main.o dijkstra.o graphe.o dico.o word.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: $(SRC)main.c $(HEADERS)
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: $(SRC)%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o exe