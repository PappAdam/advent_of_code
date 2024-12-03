CFLAGS = -Wall
LIBS = -lhelper

SRC=$(wildcard day_${d}/*.c)
HELPER=$(wildcard ../lib/*.c)

main: $(SRC)
	gcc -o day_${d}/$@ ../lib/${HELPER} $^ $(CFLAGS)
	./day_${d}/$@