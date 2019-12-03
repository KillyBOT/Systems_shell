ifeq ($(DEBUG),true)
	CC = gcc -g
else
	CC = gcc
endif

OBJECTS = main.o parse_args.o

all: $(OBJECTS) shell.h
	$(CC) -o KShell $(OBJECTS)

main.o: main.c shell.h
	$(CC) -c main.c

parse_args.o: parse_args.c shell.h
	$(CC) -c parse_args.c

run:
	./KShell

valgrind:
	valgrind --leak-check=yes ./KShell
