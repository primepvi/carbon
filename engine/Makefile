CC = clang
CFLAGS = -Wall -Wextra -g -fPIC -Iinclude -Iexternal/glad/include -Iexternal/stb/include
LDFLAGS = -shared -fvisibility=hidden -lX11 -lEGL -lGL -ldl -lm 

SRCS = $(shell find src -name "*.c") external/glad/src/glad.c external/stb/src/stb_image.c
OBJS = $(patsubst %.c,build/%.o,$(SRCS))
LIB = libcarbon.so

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(LIB)
