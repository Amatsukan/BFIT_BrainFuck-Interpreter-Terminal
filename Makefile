CC=gcc
libs= -lreadline
flags= -pipe -O1 -O2 -Ofast -O3  -fomit-frame-pointer 
deps=

%.o: %.c $(libs)
	$(CC) -c -o $@ $< $(flags)

all: basic_shell.o
	$(CC) basic_shell.o -o BFIT $(libs)

clean: 
	rm -f *.o BFIT
