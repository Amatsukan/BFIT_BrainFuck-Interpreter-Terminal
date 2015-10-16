CC=gcc
libs= -lreadline
flags=
deps=
bindir=bin

%.o: %.c
	$(CC) $(flags) -c -o $@ $<

all: shell.o machine.o utils.o colors.h
	$(CC) $(flags) shell.o -o bin/BFIT $(libs)

clean:
	rm -f *.o $(bindir)/BFIT

cleanup:
	make clean
	make
