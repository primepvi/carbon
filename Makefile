.PHONY: all engine runtime clean compile

all: engine runtime

engine:
	$(MAKE) -C engine

runtime: engine
	$(MAKE) -C runtime

clean:
	$(MAKE) -C engine clean
	$(MAKE) -C runtime clean
	rm -f compile_commands.json

compile:
	$(MAKE) clean
	bear -- $(MAKE) all
