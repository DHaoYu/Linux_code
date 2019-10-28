#include<iostream>
#include<string>
#include"threadpool.hpp"

using namespace std;

class TcpClient{
	private:
		int sock;
		string ip;
		int port;
	public:
		TcpClient(string ip_ = "127.0.0.1", int port_ = 8080)
			:ip(ip_), port(port_), sock(-1)
		{

		}

		void InitTcpClient()
		{
			sock = socket(AF_INET, SOCK_STREAM, 0);
			if(sock < 0)
			{
				cerr<<"socket error!"<<endl;
				exit(2);
			}
			//cout<<"InitTcpClient success!"<<endl;
		}

		void Run()
		{
			struct sockaddr_in server;
			server.sin_family = AF_INET;
			server.sin_port = htons(port);
			server.sin_addr.s_addr = inet_addr(ip.c_str());
			
			if(connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
			{
				cerr<<"connect error!"<<endl;
				exit(3);
			}
			for(;;)
			{
			//	cout<<"enter for ..."<<endl;
				request rq;
				response rsp;

				cout<<"please enter op# ";
				cin>>rq.op;
				while(rq.op != '+' && rq.op != '-' && rq.op != '/' && rq.op != '*' && rq.op != '%')
				{
					cout<<"enter error! try again"<<endl;
					cin>>rq.op;
					cout<<rq.op<<endl;
				}
				cout<<"please enter x, y# ";
				cin>>rq.x>>rq.y;
				send(sock, &rq, sizeof(rq), 0);
				ssize_t s = recv(sock, &rsp, sizeof(rsp), 0);
				if(s == 0)
				{
					cout<<"server exit..."<<endl;
				}
				cout<<"server return# result: "<<rsp.result<<"  status: "<<rsp.status<<endl;
			}
		}
		
		~TcpClient()
		{

		}
};


int main()
{
	TcpClient *tcp = new TcpClient();
	tcp->InitTcpClient();
	tcp->Run();
	delete tcp;

	return 0;
}
