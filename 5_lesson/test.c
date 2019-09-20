#include<unistd.h>

int main()
{
	char* const argv[]={"ls","-a",NULL};
	char* const envp[]={"PATH=/bin:/usr/bin","TERM=console",NULL};
	execl("/bin/ls","ls","-a",NULL);
	//execlp("ps","ps","-ef",NULL);
	//execve("/bin/ls",argv,envp);
}
