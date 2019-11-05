#include<iostream>
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<cstring>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

class TcpClient{
	private:
		int sock;
		string peer_ip;
		int peer_port;
	public:
		TcpClient(string ip = "127.0.0.1", int port = 8080)
			:peer_ip(ip), peer_port(port), sock(-1)
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
			peer.sin_addr.s_addr = inet_addr(peer_ip.c_str());
			peer.sin_port = htons(peer_port);
			//client链接工作
			if(connect(sock, (struct sockaddr*)&peer, sizeof(peer)) < 0)
			{
				cerr<<"connect error!"<<endl;
				return;
			}
			string message;
			char buf[1024];
			while(true)
			{
				cout<<"Please enter# ";
				cin >> message;
				write(sock, message.c_str(), message.size());
				ssize_t s = read(sock, buf, sizeof(buf)-1);
				if(s > 0)
				{
					buf[s] = 0;
					cout<<"Server echo# "<<buf<<endl;
				}
			}
		}
		~TcpClient()
		{
			if(sock > 0)
				close(sock);
		}
};
