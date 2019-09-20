#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	pid_t pid;
	printf("Before: pid %d\n",getpid());
	if(pid = fork() == -1)
	{
		perror("fork()");
		exit(1);
	}
	printf("After: pid %d,fork return : %d\n",getpid(),pid);
	return 0;
}
