CC =gcc

EXEC := programa-principal
EXEC_TEST :=  programa-testes

INCLUDE_DIRS := $(shell find include/ -type d)

CFLAGS := -c -g -Og -std=gnu99 -Wall -Wextra $(addprefix -I,$(INCLUDE_DIRS)) `pkg-config --cflags glib-2.0`

LDFLAGS := `pkg-config --libs glib-2.0` -lm

SRC_PRINCIPAL := $(shell find src/ -name "*.c" -not -name "test.c")
SRC_TESTS := $(shell find src/ -name "*.c" -not -name "principal.c")

OBJ_PRINCIPAL := $(patsubst src/%.c,build/%.o,$(SRC_PRINCIPAL))
OBJ_TESTS := $(patsubst src/%.c,build/%.o,$(SRC_TESTS))

.PHONY: all
all: $(EXEC) $(EXEC_TEST)

.PHONY: principal
principal: $(EXEC)

.PHONY: test
test: $(EXEC_TEST)

$(EXEC): $(OBJ_PRINCIPAL)
	@$(CC) $(OBJ_PRINCIPAL) $(LDFLAGS) -o $@

$(EXEC_TEST): $(OBJ_TESTS)
	@$(CC) $(OBJ_TESTS) $(LDFLAGS) -o $@

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf build/*
	rm -f $(EXEC) $(EXEC_TEST)
	rm -f resultados/*
