#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>

using namespace std;

int main()
{
	int fd1 = open("pipe1",O_RDONLY);
	int fd2 = open("pipe2",O_WRONLY);

	if(fd1 < 0 || fd2 < 0)
	{
		cerr<<"open"<<endl;
		return 1;
	}
	pid_t pid = fork();
	while(pid > 0)
	{
		char buf1[1024];
		ssize_t ret2 = read(fd1,buf1,sizeof(buf1));
		if(ret2 > 0)
		{
			buf1[ret2] = 0;
			cout<<buf1<<endl;
		}
		if(ret2 == 0)
		{
			cout<<"you exit, me to..."<<endl;
			return 1;
		}
	}
	while(pid == 0)
	{
		string buf2;
		getline(cin,buf2);
		ssize_t ret1 = write(fd2,buf2.c_str(),buf2.size());
	}
	close(fd1);
	close(fd2);
	return 0;
}
