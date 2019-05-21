BUILD_DIR := build
CONAN_PROFILE=../conan-platforms/conan-profile-$(shell uname -m).info
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
	mkdir -p build
	cd build && conan install --build=missing --profile=${CONAN_PROFILE} ..
	cd build && cmake ..
	cd build && make VERBOSE=1

clean:

test-library:
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


test-python:
	# FIXME: The mercury python3 module does not load unless
	# it is in the current directory. LD_LIBRARY_PATH does not help
	# an empty __init__ does not help either. where is the problem?
	rm -rf test/python3/mercury
	mkdir -p test/python3/mercury
	cp -v build/lib/_mercury.so test/python3/mercury
	cp -v build/src/swig/python/mercury.py test/python3/mercury
	cp -v src/swig/__init__.py test/python3/mercury
	cd test/python3 && python3 -m pytest


test: build test-library test-python

check: test

lint:
	cpplint --recursive --quiet .

docs:
	cd docs && make all
