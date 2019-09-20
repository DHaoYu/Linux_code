#include<iostream>
#include<unistd.h>
#include<string>
#include<vector>
#include<stdlib.h>
using namespace std;

//程序替换
int main()
{
	vector<string> argv;
	argv.push_back("ls");
	argv.push_back("-a");
	
	execl("bin/ps","ps","-ef",NULL);
	
	exit(0);	
}
