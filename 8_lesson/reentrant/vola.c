#include<stdio.h>
#include<signal.h>

volatile int flag = 0;

void handler(int signo)
{
	printf("i catch a signal : %d\n",signo);
	printf("and make flag from 0 to 1\n");
	flag = 1;
}

int main()
{
	signal(2,handler);
	while(!flag);
	printf("main exit!\n");
	return 0;
}
