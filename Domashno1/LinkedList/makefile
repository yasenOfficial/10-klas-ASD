all: main.exe

linkedlist.o: linkedlist.h linkedlist.c
	gcc -c linkedlist.c -o linkedlist.o

main.exe: linkedlist.o main.c
	gcc main.c linkedlist.o -o main.exe

clean:
	rm -f *.exe *.o


