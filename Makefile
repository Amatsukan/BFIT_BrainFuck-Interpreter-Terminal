CC=gcc
libs= -lreadline
flags=
deps=
bindir=bin

%.o: %.c
	$(CC) $(flags) -c -o $@ $<

all:
	make clean
	make os

clean:
	rm -f *.o $(bindir)/BFIT

os:	shell.o machine.o utils.o colors.h
	mkdir -p bin
	$(CC) $(flags) shell.o -o bin/BFIT $(libs)
