#include <stdio.h>
#include <unistd.h>

int main()
{
	int ret = fork();
	printf("hello Proc : %d!,ret : %d\n",getpid(),ret);
	sleep(1);
	return 0;
}
