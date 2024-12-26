CC =gcc

EXEC := programa-principal
EXEC_TEST := programa-testes
EXEC_INTERACTIVE := programa-interativo

INCLUDE_DIRS := $(shell find include/ -type d)

CFLAGS := -c -g -Og -std=gnu99 -Wall -Wextra $(addprefix -I,$(INCLUDE_DIRS)) `pkg-config --cflags glib-2.0` -lncurses -lpanel -lmenu

LDFLAGS := `pkg-config --libs glib-2.0` -lm -lncurses -lpanel -lmenu

SRC_PRINCIPAL := $(shell find src/ -name "*.c" -not -name "test.c" -not -name "interactive.c")
SRC_TESTS := $(shell find src/ -name "*.c" -not -name "principal.c" -not -name "interactive.c")
SRC_INTERACTIVE := $(shell find src/ -name "*.c" -not -name "principal.c" -not -name "test.c")

OBJ_PRINCIPAL := $(patsubst src/%.c,build/%.o,$(SRC_PRINCIPAL))
OBJ_TESTS := $(patsubst src/%.c,build/%.o,$(SRC_TESTS))
OBJ_INTERACTIVE := $(patsubst src/%.c,build/%.o,$(SRC_INTERACTIVE))

.PHONY: all
all: $(EXEC) $(EXEC_TEST) $(EXEC_INTERACTIVE)

.PHONY: principal
principal: $(EXEC)

.PHONY: test
test: $(EXEC_TEST)

.PHONY: interactive
interactive: $(EXEC_INTERACTIVE)

$(EXEC): $(OBJ_PRINCIPAL)
	@$(CC) $(OBJ_PRINCIPAL) $(LDFLAGS) -o $@

$(EXEC_TEST): $(OBJ_TESTS)
	@$(CC) $(OBJ_TESTS) $(LDFLAGS) -o $@

$(EXEC_INTERACTIVE): $(OBJ_INTERACTIVE)
	@$(CC) $(OBJ_INTERACTIVE) -o $@ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -rf build/*
	rm -f $(EXEC) $(EXEC_TEST) $(EXEC_INTERACTIVE)
	rm -f resultados/*
