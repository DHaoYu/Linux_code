#include<iostream>
#include<string>
#include<cstring>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;


class Server
{
private:
	int sockfd;
	int port;
	string ip;
public:
	Server(string ip_ = "127.0.0.1", int port_ = 8080)
	:sockfd(-1)
	,port(port_)
	,ip(ip_)
	{
		
	}
	void InitServer()
	{
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if(sockfd < 0)
		{
			cerr<<"socket error! exit"<<endl;
			exit(2);
		}
		
		struct sockaddr_in local;
		local.sin_family = AF_INET;
		local.sin_port = htons(port);
		local.sin_addr.s_addr = inet_addr(ip.c_str());
		
		if(bind(sockfd, (struct sockaddr* )&local, sizeof(local)) < 0)
		{
			cerr<<"bind error ! exit!" << endl;
			exit(3);
		}
		cout<<"init ... sock bind success:" << sockfd << endl;

	}
	void Start()
	{
		char buf[1024];
		struct sockaddr_in peer;
		for( ; ; )
		{
			socklen_t len = sizeof(peer);
			ssize_t s = recvfrom(sockfd, buf, sizeof(buf)-1, 0, (struct sockaddr*)&peer, &len);
			if(s > 0)
			{
				buf[s] = 0;
				cout<<"client# "<< buf << endl;
				sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&peer, len);
			}
		}
	}
	~Server()
	{

	}

};
