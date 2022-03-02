CC = g++
CFLAGS = -Wall -Wextra -Werror

all: build

build: main convert

main: main.o
	$(CC) $(CFLAGS) -o $@ $^

convert: convert.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

run: build
	./main $(problem)

labyrinth: build
	./convert
clean:
	rm -f *.o *~ main convert
	rm -f *.clear
	rm -f *.out
