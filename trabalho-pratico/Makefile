CC =gcc

EXEC := programa-principal

CFLAGS := -c -g -Og -std=gnu99 -Wall -Wextra -Iinclude `pkg-config --cflags glib-2.0`

LDFLAGS := `pkg-config --libs glib-2.0` -lm

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
