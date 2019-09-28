#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void handler(int sig)
{
	while(waitpid(-1,NULL,WNOHANG) > 0)
	{
		printf("i am father, and i get SIGCHLD signal: %d\n",sig);
		sleep(1);
	}
	printf("child is quit\n");
}

int main()
{
	signal(SIGCHLD,handler);
	pid_t id = fork();

	if(id == 0)
	{
		printf("i am child, i will 3 second later exit\n");
		sleep(3);
		exit(1);
	}

	while(1)
	{
		printf("i am father, and doing another things \n");
		sleep(1);
	}
	return 0;
}
