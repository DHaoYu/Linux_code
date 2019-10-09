#include<iostream>
#include"udpClient.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "hello client" << endl;
	Client* cp = new Client(argv[1], atoi(argv[2]));
	//Client* cp = new Client();
	cp->InitClient();
	cp->Run();
	
	return 0;
}
