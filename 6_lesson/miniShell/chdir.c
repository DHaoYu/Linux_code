#include<unistd.h>
#include<stdio.h>

int main()
{
	pid_t id = fork();
	if(id == 0)
	{
	char *dir="..";
	int ret;
	ret = chdir(dir);//chdir只对该进程有效，当
	//推出该进程后，会自动返回最初目录
	}
	else
	{
		while(1)
		{
		printf("....\n");
		sleep(1);
		}
	}
	return 0;
}
