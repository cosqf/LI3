CC =gcc

EXEC := programa-principal

INCLUDE_DIRS := $(shell find include/ -type d)

CFLAGS := -c -g -Og -std=gnu99 -Wall -Wextra $(addprefix -I,$(INCLUDE_DIRS)) `pkg-config --cflags glib-2.0`

LDFLAGS := `pkg-config --libs glib-2.0` -lm

SRC := $(shell find src/ -name "*.c")

OBJ := $(patsubst src/%.c,build/%.o,$(SRC))

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $@

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf build/*
	rm -f programa-principal
	rm -f resultados/*
