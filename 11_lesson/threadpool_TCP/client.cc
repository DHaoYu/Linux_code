#include<iostream>
#include"tcpClient.hpp"

using namespace std;

int main()
{
	TcpClient* tcp = new TcpClient();
	tcp->InitClient();
	tcp->Run();
	delete tcp;

	return 0;
}
