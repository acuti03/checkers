exe: main.o functions.o
	gcc -g -o exe main.o functions.o

main.o: main.c headers.h conio.h
	gcc -g -c main.c

functions.o: functions.c headers.h conio.h
	gcc -g -c functions.c



