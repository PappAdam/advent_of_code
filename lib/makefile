SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all:
	gcc -c ${SRC}
	ar rcs libhelper.a ${OBJ}