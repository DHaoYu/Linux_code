#include<iostream>
#include<string>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
using namespace std;

void* Routine(void* args)
{
	int sock = *(int*)args;
	char request[10240];
	ssize_t s = recv(sock, request, sizeof(request)-1, 0);
	if(s > 0)
	{
		cout<<"--------------------------------"<<endl;
		cout<<request<<endl;
		cout<<"--------------------------------"<<endl;
	
		string response = "HTTP/1.0 200 OK\r\n\r\n<html><h1>hello world</h1></html>";
		//string response = "HTTP/1.0 302 Found\r\nLocation: https://www.baidu.com\r\n\r\n<html><h1>www.baidu.com</h1></html>";

		send(sock, response.c_str(), response.size(), 0);
	}
	else if(s < 0)
	{
		cerr<<"recv error!"<<endl;
	}
	else
	{
		cout<<"client quit..."<<endl;
	}
	close(sock);
}

int main()
{
	int lis_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(lis_sock < 0)
	{
		cerr<<"socket error!"<<endl;
		exit(2);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(8080);
	local.sin_addr.s_addr = htons(INADDR_ANY);

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

	for(;;){
		struct sockaddr_in peer;
		socklen_t len = sizeof(peer);
		int sock = accept(lis_sock, (struct sockaddr*)&peer, &len);
		if(sock < 0)
		{
			cerr<<"accept error!"<<endl;
			continue;
		}
		cout<<"get a new link "<<sock<<endl;
		int* psock = new int(sock);
		pthread_t tid;
		pthread_create(&tid, NULL, Routine, (void*)psock);

	}
		return 0;
}





