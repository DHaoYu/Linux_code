#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<cstring>
#include<netinet/in.h>
#include<arpa/inet.h>
using namespace std;

class TcpClient{
	private:
		int sock;
		string peer_ip;
		int peer_port;
	public:
		TcpClient(string ip_ = "127.0.0.1", int port_ = 8080)
			:peer_ip(ip_), peer_port(port_), sock(-1)
		{

		}
		
		void InitClient()
		{
			sock = socket(AF_INET, SOCK_STREAM, 0);
			if(sock < 0)
			{
				cerr<<"socket error!"<<endl;
				exit(2);
			}
		}

		void Run()
		{
			struct sockaddr_in peer;
			peer.sin_family = AF_INET;
			peer.sin_port =htons(peer_port);
			peer.sin_addr.s_addr = inet_addr(peer_ip.c_str());
			if(connect(sock, (struct sockaddr*)&peer, sizeof(peer)) < 0)
			{
				cerr<<"connect error!"<<endl;
				exit(3);
			}

			string message;
			char buf[1024];
			while(1)
			{
				cout<<"client enter# ";
				cin>>message;
				write(sock, message.c_str(), message.size());
				ssize_t s = read(sock, buf, sizeof(buf));
				buf[s] = 0;
				cout<<"server return# "<<buf<<endl;
			}
		}

		~TcpClient()
		{

		}
};



int main(int argc, char* argv[])
{
	TcpClient* tcp = new TcpClient(argv[1], atoi(argv[2]));
	tcp->InitClient();
	tcp->Run();
	delete tcp;

	return 0;
}
