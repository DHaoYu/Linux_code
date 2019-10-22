#include<iostream>
#include"tcpServer.hpp"

using namespace std;

int main()
{
	TcpServer* tsp = new TcpServer();
	tsp->InitServer();
	tsp->Start();

	delete tsp;
	return 0;
}
