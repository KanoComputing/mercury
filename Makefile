BUILD_DIR := build
COVERAGE_DIR := coverage
COVERAGE_INFO := ${COVERAGE_DIR}/coverage.info
COVERAGE_EXCLUDES := \
	"*Qt*.framework*" \
	"*.h" \
	"*/tests/*" \
	"*.moc" \
	"*moc_*.cpp" \
	"*/test/*" \
	"*/build*/*" \
	"*Xcode.app*"

.PHONY: build lint clean test docs

all: build

build:
	cd build && conan install ..
	cd build && cmake ..
	cd build && make

clean:

test: build
	cd build && make test
	mkdir -p ${COVERAGE_DIR}
	rm -f ${COVERAGE_INFO}
	lcov --directory ${BUILD_DIR} \
		--capture \
		--output-file ${COVERAGE_INFO}
	lcov --remove ${COVERAGE_INFO} \
		--output-file ${COVERAGE_INFO} \
		--quiet \
		${COVERAGE_EXCLUDES}
	lcov --directory ${BUILD_DIR} \
		--zerocounters
	genhtml --output-directory ${COVERAGE_DIR} \
		--demangle-cpp \
		${COVERAGE_DIR}/coverage.info

check: test

lint:
	cpplint --recursive --quiet .

docs:
	cd docs && make all
