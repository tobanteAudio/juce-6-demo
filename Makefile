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

.PHONY: format
format:
	find src -iname '*.h' -o -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
