all: main.exe

dynarr.o: dynarr.h dynarr.c
	gcc -c dynarr.c -o dynarr.o

main.exe: dynarr.o main.c
	gcc main.c dynarr.o -o main.exe

clean:
	del *.exe *.o


