#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

//int main()//non-bloking wait
//{
//	pid_t ret;
//	ret = fork();
//	if(ret == -1)
//	{
//		perror("fork()");
//		exit(0);
//	}
//	else if(ret == 0)
//	{
//		printf("i am child and pid is :%d\n",getpid());
//	}
//	else
//	{
//		int sta;
//		printf("i am father and pid is :%d , i am wait my child...\n",getpid());
//		pid_t stasig = wait(&sta);
//		if(stasig == -1)
//		{
//			printf("wait fail, I counld not find my child\n");
//			exit(10);
//		}
//		else if(stasig == ret)
//		{
//			printf("wait sueecss!, my child pid is: %d\n",ret);
//			printf("child is ok ? %d\n",(sta>>8)&0xff);//right
//			printf("sig code :%d\n",sta&0x7f);
//		}
//	}
//}
//
//

int main()//bloking wait
{
	pid_t pid;
	pid = fork();

	if(pid < 0)
	{
		perror("fork()");
	}
	else if(pid == 0)
	{//child
		printf("i am child running, pid: %d\n",getpid());
		sleep(8);
		exit(10);
	}
	else
	{//father
		while(1)
		{
			int st;
			printf("i am father, waiting my child...\n");
			pid_t ret = waitpid(pid,&st,WNOHANG);
			sleep(1);
			if(ret > 0)
				exit(0);
		}
	}
}









