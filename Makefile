CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LDFLAGS=-lncurses
SRC=src/birdy_rush.c
OUT=build/birdy_rush

all: $(OUT)

$(OUT): $(SRC)
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -rf build