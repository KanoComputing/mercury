BUILD_DIR := build
CONAN_PROFILE=../conan-platforms/conan-profile-$(shell uname -s)-$(shell uname -m).info
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
	cd build && make clean

test-library:
	cd build && make coverage

test-python: build
	# Python tests can be run on a build sandbox,
	# as well as on the target installation system
	-cp -v build/lib/_mercury.so test/python3
	-cp -v build/src/swig/python/mercury.py test/python3
	cd test/python3 && python3 -m pytest $(TESTMODULE)

test: build test-library test-python

check: test

lint:
	cpplint --recursive --quiet .

docs:
	cd docs && make all
