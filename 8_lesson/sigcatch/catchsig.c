#include<stdio.h>
#include<signal.h>

void hander(int sig)
{
	printf("catch a sig : %d\n",sig);
}

int main()
{
	signal(2,hander);
	while(1)
	{
		printf("hello world\n");
		sleep(1);
	}
	return 0;
}
