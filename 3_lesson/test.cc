#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main()
{
	cout<<"pid:"<<getpid()<<endl;
	cout<<"ppid:"<<getppid()<<endl;
	return 0;
}
