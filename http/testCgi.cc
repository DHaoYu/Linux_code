#include<iostream>
#include<string>
#include<unistd.h>
#include<stdlib.h>
#include"Util.hpp"

using namespace std;

void HanderData(string& args)
{
	size_t pos = args.find('&');
	if(pos != -1)
	{
		string first = args.substr(0, pos);
		string second = args.substr(pos+1);
		cout<<first<<" "<<second<<endl;
		size_t pos1 = first.find('=');
		int data1 = Util::StringToInt(first.substr(pos+1));
		size_t pos2 = second.find('=');
		int data2 = Util::StringToInt(second.substr(pos+1));
		cout<<data1+data2<<endl;
		cerr<<data1+data2<<endl;
	}
}

int main()
{
//	cout<<"hello world"<<endl;
	string args;
	string method = getenv("METHOD");
	if(method == "GET")
	{
		args = getenv("QUERY_STRING");
	}
	else if(method == "POST")
	{
		string cl = getenv("CONTENT_LENGTH");
		int content_length = Util::StringToInt(cl);
		char c;
		while(content_length--)
		{
			read(0, &c, 1);
			args.push_back(c);
		}
	}
	else
	{

	}
	HanderData(args);
	cout<<"method: "<<method<<endl;
	cerr<<"method: "<<method<<endl;
	cout<<"args: "<<args<<endl;
	cerr<<"args: "<<args<<endl;
	return 0;
}
