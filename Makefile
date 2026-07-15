.PHONY: all engine runtime cli clean compile

all: engine runtime cli

engine:
	$(MAKE) -C engine

runtime: engine
	$(MAKE) -C runtime

cli: engine runtime
	$(MAKE) -C cli

clean:
	$(MAKE) -C engine clean
	$(MAKE) -C runtime clean
	$(MAKE) -C cli clean
	rm -f compile_commands.json

compile:
	$(MAKE) clean
	bear -- $(MAKE) all
