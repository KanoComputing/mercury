.PHONY: lint clean

all: build

build:

clean:

test:

check: test

lint:
	cpplint --recursive --quiet .
