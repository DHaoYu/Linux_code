#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<cstring>
#include<pthread.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

class TcpServer{
private:
	int sock;
	string ip;
	int port;
public:
	TcpServer(string ip_ = "127.0.0.1", int port_ = 8080)
		:ip(ip_), port(port_),sock(-1)
	{
		
	}

	void InitServer()
	{//创建套接字
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if(sock < 0)
		{
			cerr<<"socket error!"<<endl;
			exit(2);
		}
		
		struct sockaddr_in local;
		local.sin_family = AF_INET;
		local.sin_port = htons(port);
		local.sin_addr.s_addr = inet_addr(ip.c_str());
		socklen_t len = sizeof(local);
		//绑定套接字
		if(bind(sock, (struct sockaddr*)&local, len) < 0)
		{
			cerr<<"bind error!"<<endl;
			exit(3);
		}
		//监听
		if(listen(sock, 5) < 0)
		{
			cerr<<"listen error!"<<endl;
			exit(4);
		}
	}
	
	static void ServiceIO(int sock_use)
	{
		char buf[1024];
		while(true)
		{
			ssize_t s = read(sock_use, buf, sizeof(buf));
			if(s > 0)
			{
				buf[s] = 0;
				cout<<"clinet say# "<<buf<<endl;
				write(sock_use, buf, strlen(buf));
			}
			else if(s == 0)
			{
				cout<<"client quit..."<<endl;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	static void* Routine(void* args)
	{
		pthread_detach(pthread_self());
		int sockfd = *(int*)args;
		ServiceIO(sockfd);
		close(sockfd);
		delete (int*)args;	
	}
	void Start()
	{
		struct sockaddr_in peer;
		socklen_t len = sizeof(peer);
		while(true)
		{
			int sock_use = accept(sock, (struct sockaddr*)&peer, &len);
			if(sock_use < 0)
			{
				cerr<<"accpet error!"<<endl;
				continue;
			}
			pthread_t tid;
			int *p = new int(sock_use);
			cout<<"client link..."<<endl;
			pthread_create(&tid, NULL, Routine, (void*)p);
		}
	}

	~TcpServer()
	{

	}
};

int main(int argc, char* argv[])
{
	TcpServer* tsp = new TcpServer(argv[1], atoi(argv[2]));
	tsp->InitServer();
	tsp->Start();
	delete tsp;

	return 0;
}




