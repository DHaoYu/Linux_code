.PHONY:all
all:CreatFork test

CreatFork:CreatFork.c
	gcc CreatFork.c -o CreatFork
test:test.cc
	g++ -o test test.cc
.PHONY:clean
clean:
	rm -f CreatFork test
