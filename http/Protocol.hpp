#pragma once
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/sendfile.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<unordered_map>
#include<utility>
#include"Util.hpp"

#define WWW "./wwwroot"

using namespace std;

class HttpRequest{
private:
	string request_line;
	string request_header;
	string request_blank;
	string request_body;
private:
	string method;
	string uri;
	string version;
	unordered_map<string, string> header_kv;
	string path;//资源路径
	string query_string;//通过GET方法上传的参数
	int resource_size;
	bool cgi;
	string suffix;
public:
	HttpRequest():request_blank("\n"), path(WWW), resource_size(0), cgi(false)
	{
	}

	string& GetRequestLine()
	{
		return request_line;
	}
	string& GetRequestHeader()
	{
		return request_header;
	}
	string& GetRequestBody()
	{
		return request_body;
	}
	string& GetPath()
	{
		return path;
	}
	string& GetMethod()
	{
		return method;
	}

	string& GetQueryString()
	{
		return query_string;
	}
	int GetResourceSize()
	{
		return resource_size;
	}
	string GetSuffix()
	{
		return suffix;
	}
	void RequestLineParse()
	{
		//GET /index.html HTTP/1.1
		stringstream ss(request_line);
		ss>>method>>uri>>version;
		Util::StringToUpper(method);
		cout<<"method: "<<method<<endl;
		cout<<"uri:    "<<uri<<endl;
		cout<<"version:"<<version<<endl;
	}
	void RequestHeaderParse()
	{
		//key: value
		vector<string> v;
		Util::TransformToVector(request_header, v);
		for(auto it = v.begin(); it != v.end(); it++)
		{
			string key;
			string val;
			Util::MakeKV(*it, key, val);
			header_kv.insert(make_pair(key, val));
			cout<<"key: "<<key<<endl;
			cout<<"val: "<<val<<endl;
		}
	}
	void UriParse()
	{
		//POST:一定带参
		//GET: 如果包含?则一定带参
		//GET: 没有? ,则不带参
		if(method == "POST")
		{
			//POST方法
			cgi = true;
			path += uri;
		}
		else //GET 方法
		{
			size_t pos = uri.find('?');
			if(string::npos == pos)
			{
				path += uri;
			}
			else//带有?
			{
				cgi = true;
				path += uri.substr(0, pos);
				query_string = uri.substr(pos+1);
			}
		}
		if(path[path.size()-1] == '/')
		{
			path += "index.html";
		}
		size_t pos = path.rfind(".");
		if(string::npos == pos)
			suffix = ".html";
		else
			suffix  = path.substr(pos);
	}
	bool IsPathLegal()
	{
		//path / or /index
		//需要保存一下文件发小
		struct stat st;
		if(stat(path.c_str(), &st) == 0)
		{//路径合法
			if(S_ISDIR(st.st_mode))
			{
				path += "/index.html";
			}
			else
			{
				if(st.st_mode & S_IXUSR || st.st_mode & S_IXGRP ||\
						st.st_mode & S_IXOTH)
				{
					cgi = true;
				}
			}
			resource_size = st.st_size;
			return true;
		}
		else
		{//路径不合法
			return false;
		}
	}
	bool MethodIsLegal()
	{
		//GET || POST
		//strcasecmp 比较时忽略大小写
		if(method != "GET" && method != "POST")
		{
			return false;
		}
		return true;
	}
	bool IsNeedRecv()
	{
		return method == "POST";
	}
	int GetContentLength()
	{
		auto it = header_kv.find("Content-Length");
		if(it == header_kv.end())
		{
			//cout<<"Centent"<<end;
			return -1;
		}
		return Util::StringToInt(it->second);//指向的是值
	}
	bool IsCgi()
	{
		return cgi;
	}
	~HttpRequest()
	{

	}
};

class HttpResponse{
private:
	string response_line;
	string response_header;
	string response_blank;
	string response_body;
private:
	int fd;
	int size;
public:
	HttpResponse():response_blank("\r\n"), fd(-1)
	{

	}
	void MakeResponseLine(int code)
	{
		response_line += "HTTP/1.1";
		response_line += " ";
		response_line += Util::IntToString(code);
		response_line += " ";
		response_line += Util::CodeToDec(code);
		response_line += " ";
		response_line += "\r\n";
	}
	void MakeResponseHeader(vector<string>& v)
	{
		auto it = v.begin();
		for(; it != v.end(); it++)
		{
			response_header += *it;
			response_header += "\r\n";
		}
	}
	void MakeResponse(HttpRequest *rq, int code, bool cgi)
	{
		//构建响应
		MakeResponseLine(code);
		vector<string> vs;
		if(cgi)
		{
			string suffix = "";
			string ct = Util::SuffixToType(suffix);
			vs.push_back(ct);
			string cl = "Content-Length: ";
			cl += Util::IntToString(response_body.size());
			vs.push_back(cl);
			MakeResponseHeader(vs);
		}
		else
		{
			string suffix = rq->GetSuffix();
			size = rq->GetResourceSize();
			string ct = Util::SuffixToType(suffix);
			vs.push_back(ct);
			string cl = "Content-Length: ";
			cl += Util::IntToString(size);
			vs.push_back(cl);
			MakeResponseHeader(vs);

			string path = rq->GetPath();
			//可以用open打开，将读取内容放置sock
			fd = open(path.c_str(), O_RDONLY);
		}
	}

	string &GetResponseLine()
	{
		return response_line;
	}
	string &GetResponseHeader()
	{
		return response_header;
	}
	string &GetResponseBlank()
	{
		return response_blank;
	}
	string& GetResponseBody()
	{
		return response_body;
	}
	int GetFd()
	{
		return fd;
	}
	int GetResourceSize()
	{
		return size;
	}
	~HttpResponse()
	{
		if(fd != -1)
			close(fd);
	}
};

class EndPoint{
private:
	int sock;
public:
	EndPoint(int sock_):sock(sock_)
	{

	}

	int RecvLine(string& line) //\n \r \r\n --> \n
	{
		char c = 'x';
		while(c != '\n')
		{
			ssize_t s = recv(sock, &c, 1, 0);
			if(s > 0)
			{//处理
				if( c == '\r')
				{//\r or \r\n
					if(recv(sock, &c, 1, MSG_PEEK) > 0) //窥探标志位
					{
						if(c == '\n')//\r\n
							recv(sock, &c, 1, 0);
						else
							c = '\n';
					}
					else
						c = '\n';
				}
				line.push_back(c);
			}
			else
			{
				c = '\n';
				cout<<"recv error!"<<endl;
				line.push_back(c);
			}
		}
		return line.size();
	}

	void RecvRequestLine(HttpRequest* rq)
	{
		RecvLine(rq->GetRequestLine());
		//cout<<"requestline: "<<rq->GetRequestLine()<<endl;
	}
	void RecvRequestHeader(HttpRequest *rq)
	{
		string &rh = rq->GetRequestHeader();
		do{
			string line = "";
			RecvLine(line);
			if(line == "\n")
				break;
			rh += line;
		}while(1);
	}
	void RecvRequestBody(HttpRequest *rq)
	{
		int len = rq->GetContentLength();
		string& body = rq->GetRequestBody();
		//cout<<"len = "<<len<<endl;
		char c;
		while(len--)
		{
			if(recv(sock, &c, 1, 0))
			{
				body.push_back(c);
			}
		}
		cout<<"body: "<<body<<endl;
	}
	void SendResponse(HttpResponse* rsp, bool cgi)
	{
		string &response_line = rsp->GetResponseLine();
		string &response_header = rsp->GetResponseHeader();
		string &response_blank = rsp->GetResponseBlank();
		send(sock, response_line.c_str(), response_line.size(), 0);
		send(sock, response_header.c_str(), response_header.size(), 0);
		send(sock, response_blank.c_str(), response_blank.size(), 0);
		if(cgi)
		{
			string &response_body = rsp->GetResponseBody();
			send(sock, response_body.c_str(), response_body.size(), 0);
		}
		else
		{
			int fd = rsp->GetFd();
			int size = rsp->GetResourceSize();
			sendfile(sock, fd, NULL, size);
		}
		
	}
	~EndPoint()
	{
		if(sock >= 0)
			close(sock);
	}
};


class Entry{
	public:
		static int ProcessCgi(HttpRequest *rq, HttpResponse *rsp, int code)
		{
			string path = rq->GetPath();
			string& body = rq->GetRequestBody();
			string& method = rq->GetMethod(); 
			string& query_string = rq->GetQueryString();
			int content_length = rq->GetContentLength();
			string cont_len_env = "CONTENT_LENGTH=";
			string method_env = "METHOD=";
			method_env += method;
			string query_string_env = "QUERY_STRING=";
			query_string_env += query_string;
			string& rsp_body = rsp->GetResponseBody();
			//站在子进程cgi角度
			int input[2] = {0};
			int output[2] = {0};
			pipe(input);
			pipe(output);
			
			pid_t id = fork();
			if(id < 0)
			{
				//
				code = 404;
			}
			else if(id == 0)
			{//子进程
				close(input[1]);
				close(output[0]);
				dup2(input[0], 0);
				dup2(output[1], 1);
				putenv((char*)method_env.c_str());
				
				if(method == "POST")
				{
					cont_len_env += Util::IntToString(content_length);
					putenv((char*)cont_len_env.c_str());
				}
				else if(method == "GET")
				{
					putenv((char*)query_string_env.c_str());
				}
				else
				{
					code = 404;
				}
				//如果是 GET方法， query_string ->env
				//如果是 POST方法，body-> stdin stdout
				execl(path.c_str(), path.c_str(), NULL);
				exit(1);
			}
			else//父进程
			{
				close(input[0]);
				close(output[1]);
				if(method == "POST")
				{
					auto it = body.begin();
					for(; it != body.end(); it++)
					{
						char c = *it;
						write(input[1], &c, 1);
					}
				}
				char c;
				while(read(output[0], &c, 1) > 0)
				{
					rsp_body.push_back(c);
				}
				waitpid(id, NULL, 0);
			}
			return code;
		}
			//1. 通过endpoint 读取请求，并且构建request
			//2. 分析request 得出具体细节
			//3. 构建response
			//4. 通过endpoint 返回response，最后中完成请求/响应， close(sock)
			//上述步骤，可能彼此交叉进行
		static void *HandlerRequest(void *args)
		{
			int code = 200;
			int *p = (int*)args;
			int sock = *p;
			EndPoint *ep = new EndPoint(sock);
			HttpRequest *rq = new HttpRequest();
			HttpResponse *rsp = new HttpResponse();
			ep->RecvRequestLine(rq);//读取行
			rq->RequestLineParse();
			if(!rq->MethodIsLegal())//非法方法method
			{
				//
				code = 404;
				goto end;

			}
			//合法之后，需要接收请求报头
			ep->RecvRequestHeader(rq);
			rq->RequestHeaderParse();
			if(rq->IsNeedRecv())
			{
				ep->RecvRequestBody(rq);
			}
			//分析uri
			rq->UriParse();
			if(!rq->IsPathLegal())
			{
				code = 404;
				goto end;
			}
			if(rq->IsCgi())
			{
				//do cgi
				code = ProcessCgi(rq, rsp, code);
				rsp->MakeResponse(rq, code, true);
				ep->SendResponse(rsp, true);
			}
			else
			{
				rsp->MakeResponse(rq, code, false);
				ep->SendResponse(rsp, false);
			}


		end:
			delete rq;
			delete rsp;
			delete ep;
			delete p;
		}
};
