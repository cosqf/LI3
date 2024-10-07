CC =gcc

EXEC := programa-principal

CFLAGS = -c -g -Wall -Wextra -Iinclude -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include

LDFLAGS = `pkg-config --libs glib-2.0`

SRC := $(shell find src/ -name "*.c")

OBJ := $(SRC:src/%.c=build/%.o)

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $@

build/%.o: src/%.c
	@mkdir -p build
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf build/*
	rm -f programa-principal
	rm -f resultados/*.txt
