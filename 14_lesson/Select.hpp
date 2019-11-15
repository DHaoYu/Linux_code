#pragma once

#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<vector>
#include<algorithm>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

using namespace std;

class SelectServer{
	private:
		int lis_sock;
		int port;
	public:
		SelectServer(int _port = 8080)
			:port(_port), lis_sock(-1)
		{
		}

		void InitServer()
		{
			lis_sock = socket(AF_INET, SOCK_STREAM, 0);
			if(lis_sock < 0)
			{
				cerr<<"socket error!"<<endl;
				exit(2);
			}

			struct sockaddr_in local;
			local.sin_family = AF_INET;
			local.sin_port = htons(port);
			local.sin_addr.s_addr = htonl(INADDR_ANY);
			if(bind(lis_sock, (struct sockaddr*)&local, sizeof(local)) < 0)
			{
				cerr<<"bind error!"<<endl;
				exit(3);
			}
			if(listen(lis_sock, 5) < 0)
			{
				cerr<<"listen error!"<<endl;
				exit(4);
			}
		}
		
		void Run()
		{ 
			vector<int> fd_arr(sizeof(fd_set)*8, -1);
			fd_arr[0] = lis_sock;
			fd_set rfdset;
			for(;;){
				struct sockaddr_in peer;
				socklen_t len = sizeof(peer);
				struct timeval timeout ={3, 0};
				FD_ZERO(&rfdset);
				for(int i = 0; i < fd_arr.size(); i++)
				{
					if(fd_arr[i] == -1)
						continue;
					FD_SET(fd_arr[i], &rfdset);
				}
				int fd = select(*max_element(fd_arr.begin(), fd_arr.end()) +1, &rfdset, NULL, NULL, &timeout);
				if(fd < 0)
				{
					cerr<<"select error!"<<endl;
					continue;
				}
				else if(fd == 0)
				{
					cout<<"timeout ..."<<endl;
					continue;
				}
				else
				{
					for(int i = 0; i < fd_arr.size(); i++)
					{
						if(FD_ISSET(fd_arr[i], &rfdset))
						{
							cout<<"listen sock is: "<<lis_sock<<endl;
							if(fd_arr[i] == lis_sock)
							{
								int sock = accept(lis_sock, (struct sockaddr*)&peer, &len);
								if(sock < 0)
								{
									cerr<<"accept error!"<<endl;
									continue;
								}
								cout<<"get a new link..."<<endl;
								cout<<"sock is:"<<sock<<endl;
								int j = 1;
								for(; j < fd_arr.size(); j++)
								{
									if(fd_arr[j] == -1)
										break;
								}
								if(j == fd_arr.size())
								{
									cout<<"fd array is full!"<<endl;
									close(sock);
								}
								else
								{
									fd_arr[j] = sock;
								}
							}
							else
							{
								cout<<"IO......"<<endl;
								char buf[1024];
								ssize_t s = recv(fd_arr[i], buf, sizeof(buf), 0);
								if(s > 0)
								{
									buf[s] = 0;
									cout<<"client# "<<buf<<endl;
								}
								else if(s == 0)
								{
									cout<<"client quit..."<<endl;
								close(fd_arr[i]);
								fd_arr[i] = -1;
								}
								else
								{
									cerr<<"recv error!"<<endl;
									close(fd_arr[i]);
									fd_arr[i] = -1;
								}
							}	
						}
					}
				}		
		}
	}
		~SelectServer()
		{
			if(lis_sock >= 0)
			{
				close(lis_sock);
			}
		}
};





