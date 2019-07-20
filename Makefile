BUILD_DIR := build
RELEASE :=
CONAN_PROFILE=../../conan-platforms/conan-profile-$(shell uname -s)-$(shell uname -m).info

.PHONY: build lint clean test docs

all: build-release

_build:
	mkdir -p build/$(RELEASE)
	-conan remote add dev-server http://dev.kano.me:9300 || conan remote update dev-server http://dev.kano.me:9300
	-cd build/$(RELEASE) && conan install -r dev-server --build=missing --profile=${CONAN_PROFILE} ../..
	cd build/$(RELEASE) && conan install --build=missing --profile=${CONAN_PROFILE} ../..
	cd build/$(RELEASE) && cmake -DCMAKE_BUILD_TYPE=$(RELEASE) ../..
	cd build/$(RELEASE) && make VERBOSE=1

build-debug: RELEASE=Debug
build-debug: _build

build-release: RELEASE=Release
build-release: _build

build: build-release

clean:
	-cd build/Release && make clean
	-cd build/Debug && make clean

test-library: build-debug
	cd build/Debug && CTEST_OUTPUT_ON_FAILURE=1 make coverage

test-python: build-release
	# Python tests can be run on a build sandbox,
	# as well as on the target installation system
	-cp -v build/Release/lib/_mercury_python3.so test/python3/_mercury.so
	-cp -v build/Release/lib/libmercury.dylib test/python3
	-cp -v build/Release/src/swig/python/mercury.py test/python3
	cd test/python3 && python3 -m pytest $(TESTMODULE)

test-python2: build-release
	-cp -v build/Release/lib/_mercury_python2.so test/python2/_mercury.so
	-cp -v build/Release/lib/libmercury.dylib test/python2
	-cp -v build/Release/src/swig/python2/mercury.py test/python2
	cd test/python2 && python -m pytest $(TESTMODULE)

test: build-debug test-library test-python test-python2

check: test

lint:
	cpplint --recursive --quiet .

docs:
	cd docs && make all
