SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all:
	gcc -c -fPIC ${SRC}
	ar rcs libhelper.lib ${OBJ}