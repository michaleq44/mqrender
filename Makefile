CC = cc
CFLAGS = --std=c2x -Iinc -Wall -Wextra -c
ifdef release
	CFLAGS += -O3
else
	CFLAGS += -g
endif

ifndef DESTDIR
	DESTDIR=/usr/local
endif

LDFLAGS = -shared -lm

SRC_DIR = src
OBJ_DIR = bin/obj
BIN_DIR = bin

SRC_FILES = $(SRC_DIR)/draw.c \
			$(SRC_DIR)/buffer.c \
			$(SRC_DIR)/types.c
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
BINARY = libmqrender.so

all: $(BIN_DIR)/$(BINARY)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR)/$(BINARY): $(OBJ_FILES) $(BIN_DIR)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

test: all
	gcc test.c --std=c2x -Lbin -I. -lmqrender -o test 

install: all
	install "$(BIN_DIR)/$(BINARY)" "$(DESTDIR)/lib"

clean:
	rm -f $(OBJ_FILES) "$(BIN_DIR)/$(BINARY)"
	rm -f test

.PHONY: all clean
