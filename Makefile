CC=gcc
libs= -lreadline
flags= -pipe -O3
deps=

%.o: %.c $(libs)
	$(CC) -c -o $@ $< $(flags)

all: basic_shell.o
	$(CC) basic_shell.o -o BFIT $(libs)

clean: 
	rm -f *.o BFIT
