#include<iostream>
#include"ThreadPool.hpp"
#include<sys/socket.h>
#include<sys/types.h>
#include<string>
#include<cstring>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

class TcpServer{
	private:
		string ip;
		int port;
		int listen_sock;
		ThreadPool* tp;
	public:
		TcpServer(string _ip = "127.0.0.1", int _port = 8080)
			:ip(_ip), port(_port), listen_sock(-1), tp(NULL)
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
			local.sin_port = port;
			local.sin_family = AF_INET;
			local.sin_addr.s_addr = inet_addr(ip.c_str());
			if(bind(listen_sock,(struct sockaddr*)&local, sizeof(local)) < 0)
			{
				cerr<<"bind error!"<<endl;
				exit(3);
			}

			if(listen(listen_sock, 6) < 0)
			{
				cerr<<"listen error"<<endl;
				exit(4);
			}
			tp = new ThreadPool();
			tp->InitThreadPool();
		}
		
//		static void ServiceIO(int sock)
//		{
//			char buf[1024];
//			while(1)
//			{
//				ssize_t s = recv(sock, buf, sizeof(buf)-1, 0);
//				if(s > 0)
//				{
//					buf[s] = 0;
//					cout<<"client say# "<<buf<<endl;
//					send(sock, buf, strlen(buf), 0);
//				}
//				else if(s < 0)
//				{
//					cerr<<"server recv error!"<<endl;
//				}
//				else
//				{
//					break;
//				}
//			}
//		}

//		static void* Routine(void* args)
//		{
//			pthread_detach(pthread_self());
//			int sockfd = *(int*)args;
//			ServiceIO(sockfd);
//			close(sockfd);
//		}
//
		void Start()
		{
			while(true)
			{
				struct sockaddr_in peer;
				socklen_t len = sizeof(peer);
				int sock = accept(listen_sock,(struct sockaddr*)&peer, &len);
				if(sock < 0)
				{
					cerr<<"accept error!"<<endl;
					continue;
				}
				cout<<"get a client link..."<<endl;
				Task t(sock);
				
				tp->PushTask(t);
				//pthread_t tid;
				//int* p = &sock;
				//pthread_create(&tid, NULL, Routine, (void*)p);
			}
		}

		~TcpServer()
		{
			if(listen_sock > 0)
			{
				close(listen_sock);
			}
			delete tp;
		}
};




