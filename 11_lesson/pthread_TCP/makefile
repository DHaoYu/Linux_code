cc=g++
flags=-g

.PHONY:all
all:tcpClient tcpServer

tcpClient:tcpClient.cc
	$(cc) -o $@ $^ $(flags) -lpthread
tcpServer:tcpServer.cc
	$(cc) -o $@ $^ $(flags) -lpthread

.PHONY:clean
clean:
	rm -rf tcpClient tcpServer
