#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

using namespace std;

int main()
{
	
	int fd = open("./namedpipe",O_WRONLY);
	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	string buf;
	while(1)
	{
		cout<<"Plesae write ..."<<endl;
		getline(cin,buf);
		ssize_t s = write(fd,buf.c_str(),buf.size());
	}
	close(fd);
	return 0;
}
