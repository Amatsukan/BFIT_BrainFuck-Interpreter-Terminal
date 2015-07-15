CC=gcc
libs= -lreadline -lncurses
flags= -pipe -O3
deps=

%.o: %.c $(libs)
	$(CC) -c -o $@ $< $(flags)

all: basic_shell.o
	$(CC) basic_shell.o -o shells $(libs)

clean: 
	rm -f *.o shells
