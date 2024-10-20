CC =gcc

EXEC := programa-principal
EXEC_TEST :=  programa-testes

INCLUDE_DIRS := $(shell find include/ -type d)

CFLAGS := -c -g -Og -std=gnu99 -Wall -Wextra $(addprefix -I,$(INCLUDE_DIRS)) `pkg-config --cflags glib-2.0`

LDFLAGS := `pkg-config --libs glib-2.0` -lm

SRC := $(shell find src/ -name "*.c")

OBJ := $(patsubst src/%.c,build/%.o,$(SRC))

.PHONY: all
all: $(EXEC) $(EXEC_TEST)

$(EXEC): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $@

$(EXEC_TEST): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $@

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf build/*
	rm -f programa-principal programa-testes
	rm -f resultados/*
