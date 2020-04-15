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


.PHONY: sanitize
sanitize:
	cmake -S. -G$(GENERATOR) -Bbuild_sanitize \
		-DTOBANTEAUDIO_BUILD_ASAN=ON \
		-DTOBANTEAUDIO_BUILD_UBSAN=ON \
		.
	cmake --build build_sanitize
	cd build_sanitize && ctest -c

.PHONY: coverage
coverage:
	cmake -S. -G$(GENERATOR) -B build_coverage -DTOBANTEAUDIO_BUILD_COVERAGE=ON
	cd build_coverage && cmake --build .
	cd build_coverage && lcov -c -i -d . --base-directory . -o base_cov.info
	cd build_coverage && ctest
	cd build_coverage && lcov -c -d . --base-directory . -o test_cov.info
	cd build_coverage && lcov -a base_cov.info -a test_cov.info -o cov.info
	cd build_coverage && lcov --remove cov.info "*boost/*" -o cov.info
	cd build_coverage && lcov --remove cov.info "*3rd_party/*" -o cov.info
	cd build_coverage && lcov --remove cov.info "*c++*" -o cov.info
	cd build_coverage && lcov --remove cov.info "*v1*" -o cov.info
	cd build_coverage && lcov --remove cov.info "*x86_64-linux-gnu*" -o cov.info
	cd build_coverage && lcov --remove cov.info "*Xcode.app*" -o cov.info

.PHONY: report
report:
	cd build_coverage && genhtml cov.info --output-directory lcov

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: format
format:
	find plugin -iname '*.h' -o -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
	find tests -iname '*.h' -o -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
