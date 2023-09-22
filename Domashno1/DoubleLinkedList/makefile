all: main.exe

doublelinkedlist.o: doublelinkedlist.h doublelinkedlist.c
	gcc -c doublelinkedlist.c -o doublelinkedlist.o

main.exe: doublelinkedlist.o main.c
	gcc main.c doublelinkedlist.o -o main.exe

clean:
	rm -f *.exe *.o


