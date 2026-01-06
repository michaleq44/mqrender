CC = cc
CFLAGS = --std=c2x -Iinc -Iinc/mqrender -Wall -Wextra -pedantic -c
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

test:
	gcc test.c -g -lmqrender -lSDL2 -D_GNU_SOURCE=1 -D_REENTRANT -o test

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR)/$(BINARY): $(OBJ_FILES) $(BIN_DIR)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

install: all
	mkdir -p "$(DESTDIR)/lib"
	mkdir -p "$(DESTDIR)/include/mqrender"
	install -Dm 755 "$(BIN_DIR)/$(BINARY)" "$(DESTDIR)/lib"
	install -Dm 644 inc/mqrender.h "$(DESTDIR)/include/"
	install -Dm 644 inc/mqrender/* "$(DESTDIR)/include/mqrender/"

uninstall:
	rm -f "$(DESTDIR)/lib/$(BINARY)"
	rm -f "$(DESTDIR)/include/mqrender.h"
	rm -rf "$(DESTDIR)/include/mqrender"

clean:
	rm -f $(OBJ_FILES) "$(BIN_DIR)/$(BINARY)"
	rm -f test

.PHONY: all clean test install uninstall