#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	printf("hello world");
	//exit(0);//close any stream
	_exit(0);// not this step
}
