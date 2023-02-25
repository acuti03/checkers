checkers: main.o functions.o
	gcc -g -lncurses -o checkers main.o functions.o

main.o: main.c headers.h
	gcc -g -c main.c

functions.o: functions.c headers.h
	gcc -g -c functions.c