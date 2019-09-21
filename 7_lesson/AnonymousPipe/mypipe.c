#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

/*
int main()
{
	int fd[2];
	int ret=pipe(fd);
	pid_t pid=fork();
	if(pid==0)
	{//child write
		while(1)
		{
			sleep(3);
			close(fd[0]);
			char buf[] = "i am child, writing...";
			write(fd[1],buf,sizeof(buf));
		}
	}
	else if(pid>0)
	{//father read
		close(fd[1]);
		while(1)
		{
			char* buf[1024];
			read(fd[0],buf,sizeof(buf));
			printf("father read : %s\n",buf);
		}
	}
	return 0;
}
*/

int main()
{
	int fd[2];
	int ret = pipe(fd);
	if(ret == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork");
		exit(2);
	}
	else if(pid == 0)
	{
		//child write
		close(fd[0]);
		char buf[] = "i am child ,i am running...";
		while(1)
		{
			sleep(2);
			write(fd[1],buf,strlen(buf));
		}
		close(fd[1]);
	}
	else
	{
		//father read but mins close(fd[0])
		char buf[1024];
		read(fd[0],buf,sizeof(buf));
		printf("i am father read :%s \n",buf);
		close(fd[0]);
		waitpid(pid,NULL,0);
	}

}







