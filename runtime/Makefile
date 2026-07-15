CC = clang
CFLAGS = -Wall -Wextra -g -fPIC -Iinclude -I../engine/include/ -I../engine/external/glad/include -I../engine/external/stb/include -Iexternal/cJSON/include
LDFLAGS = -shared -fvisibility=hidden -L../engine -llua -lEGL -lcarbon -Wl,-rpath,'$$ORIGIN/../engine'

SRCS = $(shell find src -name "*.c") external/cJSON/src/cJSON.c
OBJS = $(patsubst src/%.c,build/%.o,$(SRCS))
BIN = librcarbon.so

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(BIN)
