#include<iostream>
#include"udpServer.hpp"
using namespace std;

void Usage(string str)
{
	cout<<"usage : IP port"<<endl;
}

int main(int argc, char* argv[])
{
	//if(argc != 3)
	//{
	//	Usage(argv[0]);
	//	exit(0);
	//}
	
	Server *sp = new Server(argv[1], atoi(argv[2]));
	//Server *sp = new Server();
	sp->InitServer();
	sp->Start();
	delete sp;

	return 0;
}
