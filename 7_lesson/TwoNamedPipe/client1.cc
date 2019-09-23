#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>

using namespace std;

int main()
{
	int fd1 = open("pipe1",O_WRONLY);
	int fd2 = open("pipe2",O_RDONLY);

	if(fd1 < 0 || fd2 < 0)
	{
		cerr<<"open"<<endl;
		return 1;
	}
	pid_t pid = fork();
	while(pid > 0)
	{
		char buf2[1024];
		ssize_t ret2 = read(fd2,buf2,sizeof(buf2));
		if(ret2 > 0)
		{
			buf2[ret2] = 0;
			cout<<buf2<<endl;
		}
		if(ret2 == 0)
		{
			cout<<"you exit, me to..."<<endl;
			return 1;
		}
	}
	while(pid == 0)
	{
		string buf1;
		getline(cin,buf1);
		ssize_t ret1 = write(fd1,buf1.c_str(),buf1.size());
	}
	close(fd1);
	close(fd2);
	return 0;
}
