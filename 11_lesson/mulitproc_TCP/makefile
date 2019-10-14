cc=g++
flags=-g;

.PHONY:all
all:tcpClient tcpServer

tcpClient:tcpClient.cc
	$(cc) -o $@ $^ $(flags)
tcpServer:tcpServer.cc
	$(cc) -o $@ $^ $(flags)

.PHONY:clean
clean:
	rm -rf tcpClient tcpServer
