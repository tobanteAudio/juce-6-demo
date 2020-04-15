CONFIG ?= Release
GENERATOR ?= Ninja
BUILD_DIR ?= build

.PHONY: all
all: config build test

.PHONY: config
config: 
	cmake -S. -B$(BUILD_DIR) -G$(GENERATOR)

.PHONY: build
build:
	cmake --build $(BUILD_DIR) --config $(CONFIG)

.PHONY: test
test:
	cd $(BUILD_DIR) && ctest

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: format
format:
	find plugin -iname '*.h' -o -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
	find tests -iname '*.h' -o -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
