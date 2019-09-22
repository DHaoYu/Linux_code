#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

using namespace std;

int main()
{
	//--->using function creat namedpipe
	//int ret = mkfifo("./namedpipe",0664);
	//if(ret < 0)
	//{
	//	perror("mkfifo");
	//	return 1;
	//}
	
	int fd = open("./namedpipe",O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	while(1)
	{
		
		char buf[1024];
		cout<<"Plesae wait ..."<<endl;
		ssize_t s = read(fd,buf,sizeof(buf)-1);
		if(s > 0)
		{
			buf[s] = 0;
			cout<<"client say#"<<buf<<endl;
		}
		else if(s == 0)
		{
			cout<<"client quit,exit now!"<<endl;
			return 1;
		}
		else
		{
			perror("read");
			return 1;
		}
	}
	close(fd);
	return 0;
}
