exe: main.o
	gcc -o exe main.o

main.o: main.c
	gcc -g -c main.c
clean:
	rm exe main.o
