#include<stdio.h>

int main()
{
	raise(9);
	while(1)
	{
		printf("pid is : %d\n",getpid());
	}

	//printf("pid is : %d\n",getpid());
	//while(1);
	//int a = 0;
	//printf("%d\n",100/a);

//	while(1)
//	{
//		printf("i am process, i am waiting singal!\n");
//		sleep(1);
//	}
	return 0;
}
