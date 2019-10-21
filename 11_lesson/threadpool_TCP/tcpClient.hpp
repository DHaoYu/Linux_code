#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string>
#include<cstring>
#include<arpa/inet.h>


using namespace std;

class TcpClient{
	private:
		string ip;
		int port;
		int sock;
	public:
		TcpClient(string _ip = "127.0.0.1", int _port = 8080)
			:ip(_ip), port(_port), sock(-1)
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

			struct sockaddr_in peer;
			peer.sin_family = AF_INET;
			peer.sin_port = port;
			peer.sin_addr.s_addr = inet_addr(ip.c_str());

			if(connect(sock, (struct sockaddr*)&peer, sizeof(peer)) < 0)
			{
				cerr<<"connect error!"<<endl;
				exit(3);
			}
		}

		void Run()
		{
			string message;
			char buf[1024];
			for(; ;)
			{
				cout<<"client eoch# ";
				cin>>message;
				send(sock, message.c_str(), message.size(), 0);
				ssize_t s = recv(sock, buf, sizeof(buf)-1, 0);
				if(s < 0)
				{
					cerr<<"recv error!"<<endl;
					continue;
				}
				else if(s == 0)
				{
					break;
				}
				else
				{
					buf[s] = 0;
					cout<<"server return# "<<buf<<endl;
				}
			}
		}

		~TcpClient()
		{

		}
};
