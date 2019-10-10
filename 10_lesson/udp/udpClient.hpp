#include<iostream>
#include<string>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>

using namespace std;

class Client
{
private:
	int sockfd;
	int peer_port;
	string peer_ip;
public:
	Client(string ip_ = "127.0.0.1", int port_ = 8080)
	:sockfd(-1)
	,peer_ip(ip_)
	,peer_port(port_)
	{
		
	}
	void InitClient()
	{
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);
		if(sockfd < 0)
		{
			cerr<< "socket error! exit!" << endl;
			exit(2);
		}
	}
	void Run()
	{
		bool quit = false;
		string message;
		char buf[1024];
		while(!quit)
		{
			struct sockaddr_in peer;
			peer.sin_family = AF_INET;
			peer.sin_addr.s_addr = inet_addr(peer_ip.c_str());
			peer.sin_port = htons(peer_port);
			socklen_t len = sizeof(peer);
			cout << "Please enter# ";
			cin >> message;
			sendto(sockfd, (void*)message.c_str(), message.size(), 0, (struct sockaddr*)&peer, len);
			ssize_t s = recvfrom(sockfd, buf, sizeof(buf)-1, 0, (struct sockaddr*)&peer, &len);
			if(s > 0)
			{
				buf[s] = 0;
				cout<<"serve echo# "<< buf << endl;
			}
		}
	}
	~Client()
	{
	}
};
