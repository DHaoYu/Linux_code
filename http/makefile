.PHONY:all
all:server testCgi
testCgi:testCgi.cc
	g++ -o $@ $^
server:server.cc
	g++ -o $@ $^ -std=c++11 -lpthread

.PHONY:clean
clean:
	rm -f server testCgi
