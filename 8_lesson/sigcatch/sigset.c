#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

int main()
{
	sigset_t set,oldset;
	sigemptyset(&set);
	oldset = set;
	sigaddset(&set,SIGINT);
	sigprocmask(SIG_BLOCK,&set,&oldset);
	
	while(1)
	{
		int i=0;
		sigpending(&set);
		for(i=1;i<=31;i++)
		{
			if(sigismember(&set,i))
				printf("1 ");
			else
				printf("0 ");
		}
		printf("\n");
		sleep(1);
	}
	return 0;
}
