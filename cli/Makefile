CC = clang
CFLAGS = -Wall -Wextra -g -I../engine/include/ -I../engine/external/glad/include -I../engine/external/stb/include -I../runtime/include -I../runtime/external/cJSON/include
LDFLAGS = -L../engine -L../runtime -llua -lEGL -lcarbon -Wl,-rpath,'$$ORIGIN/../engine' -lrcarbon -Wl,-rpath,'$$ORIGIN/../runtime'

SRCS = $(shell find src -name "*.c")
OBJS = $(patsubst src/%.c,build/%.o,$(SRCS))
BIN = cli

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(BIN)
