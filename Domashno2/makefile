all: main.exe

vector.o: vector.h vector.c
	gcc -c vector.c -o vector.o

main.exe: vector.o main.c
	gcc main.c vector.o -o main.exe

clean:
	del -f *.exe *.o


