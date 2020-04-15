CONFIG ?= Release

.PHONY: all
all: config build

.PHONY: config
config: 
	cmake -S. -Bbuild

.PHONY: build
build:
	cmake --build build --config $(CONFIG)

.PHONY: clean
clean:
	rm -rf build
