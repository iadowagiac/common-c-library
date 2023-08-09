.PHONY: all clean check

all:

clean:
	cd testsuite && make clean
	cd templates && make clean

check: all
	cd testsuite && make check
	cd templates && make check

