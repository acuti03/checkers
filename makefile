game: main.o functions.o
	gcc -g -o game main.o functions.o -lncurses

main.o: main.c headers.h
	gcc -g -c main.c

functions.o: functions.c headers.h
	gcc -g -c functions.c