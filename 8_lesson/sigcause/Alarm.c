#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int count=0;

void hander(int signo)
{
	printf("count: %d\n",count);
	exit(1);
}

int main()
{
	alarm(1);
	signal(14,hander);
	while(1)
		count++;
	//while(1)
	//{
	//	printf("count: %d\n",count++);
	//}
	return 0;
}
