CFLAGS = -Wall
LIBS = -lhelper

SRC=$(wildcard day_${t}/*.c)

main: $(SRC)
	gcc -o day_${t}/$@ $^ $(CFLAGS) -L../lib $(LIBS)
	./day_${t}/$@