CC = gcc
CFLAGS = -Iinclude
SRC = src/main.c
OBJ = build/main.o
EXEC = build/game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*
