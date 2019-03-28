.PHONY: build lint clean test docs

all: build

build:
	cd build && conan install ..
	cd build && cmake ..
	cd build && make

clean:

test:

check: test

lint:
	cpplint --recursive --quiet .

docs:
	cd docs && make all
