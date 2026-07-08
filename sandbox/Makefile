CC = clang
CFLAGS = -Wall -Wextra -g -Isrc -I../engine/src/ -I../engine/external/glad/include -I../engine/external/stb/include
LDFLAGS = -L../engine -lEGL -lcarbon -Wl,-rpath,'$$ORIGIN/../engine'
SRCS = $(shell find src -name "*.c")
OBJS = $(patsubst src/%.c,build/%.o,$(SRCS))
BIN = sandbox

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(BIN)
