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

class TcpServer{
	private:
		int listen_sock;//监听套接字，获取新连接用
		string ip;
		int port;
	public:
		TcpServer(string ip_ = "127.0.0.1", int port_ = 8080)
			:ip(ip_),port(port_),listen_sock(-1)
		{
		}

		void InitServer()
		{
			listen_sock = socket(AF_INET, SOCK_STREAM, 0);
			if(listen_sock < 0)
			{
				cerr<<"socket error!"<<endl;
				exit(2);
			}
			
			struct sockaddr_in local;
			local.sin_family = AF_INET;
			local.sin_addr.s_addr = inet_addr(ip.c_str());
			local.sin_port = htons(port);
			
			if(bind(listen_sock, (struct sockaddr*)&local, sizeof(local)) < 0)
			{
				cerr<<"bind error!"<<endl;
				exit(3);
			}
			//listen把套接字信息设置为监听状态
			if(listen(listen_sock, 5) < 0)
			{
				cerr<<"linten error!"<<endl;
				exit(4);
			}
		}
		void ServiceIO(int sock)
		{
			char buf[1024];
			while(true)
			{
				ssize_t s = read(sock, buf, sizeof(buf)-1);
				if(s > 0)
				{
					buf[s] = 0;
					cout<< "client# "<<buf<<endl;
					write(sock, buf, strlen(buf));
				}//tcp读取时s返回为0表示对端链接关闭
				else if(s == 0)
				{
					cout<< "client quit ..." <<endl;
					break;
				}
				else
				{
					cerr<<"read error!"<<endl;
				}
			}
		}
		void Start()
		{
			struct sockaddr_in peer;
			while(true)
			{
				socklen_t len = sizeof(peer);
				int sock = accept(listen_sock, (struct sockaddr*)&peer, &len);//输入输出型参数len，peer
				if(sock < 0)
				{
					cerr<<"accept error!"<<endl;
					continue;
				}
				cout<<"get a new client..."<<endl;
				//走到这块---进行服务
				ServiceIO(sock);
				close(sock);
			}
		}

		~TcpServer()
		{
		}
};



