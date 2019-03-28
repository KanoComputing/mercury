.PHONY: build lint clean test docs

all: build

build:

clean:

test:

check: test

lint:
	cpplint --recursive --quiet .

docs:
	cd docs && make all
