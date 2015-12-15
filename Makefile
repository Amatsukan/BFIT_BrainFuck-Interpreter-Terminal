CC=clang
DCC=gcc
libs= -lreadline
flags= -std=c99
deps=
bindir=bin

%.o: %.c
	$(CC) -g -c -o $@ $<  $(flags)

all:
	make clean
	make os

clean:
	rm -f *.o $(bindir)/BFIT

debug:
	make clean
	make debugBuild

debugBuild: shell.o machine.o utils.o colors.h definitions.h
	mkdir -p bin
	$(DCC) -g3 -gdb machine.o -o bin/BFIT $(libs) $(flags)

os:	shell.o machine.o utils.o colors.h definitions.h
	mkdir -p bin
	$(CC) shell.o -o bin/BFIT $(libs) $(flags)
