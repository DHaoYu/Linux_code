#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sa_handler(int signo)
{
	while(1)
	{
		printf("catch a sig:%d\n",signo);
		sleep(1);
	}
}

int main()
{	
	struct sigaction act,oact;
	act.sa_handler = SIG_INT;
	sigaction(2,&act,NULL);

	return 0;
}
