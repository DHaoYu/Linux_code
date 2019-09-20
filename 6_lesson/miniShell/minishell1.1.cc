#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;

void runShell(vector<string>& v)
{
	static char* argv[32];
	for(size_t i=0;i<v.size();i++)
	{
		argv[i]=(char*)v[i].c_str();
	}
	argv[v.size()]=NULL;
	pid_t pid = fork();
	if(pid<0)
	{
		perror("fork()");
	}
	else if(pid == 0)
	{
		if(v[0] == "cd")
			chdir(argv[1]);
		else
			execvp((char*)v[0].c_str(),argv);
	}
	else
	{
		waitpid(pid,NULL,0);
	}
	return;
}

void transStr(string& cmd)
{
	vector<string> v;
	size_t begin=0;
	size_t end;
	while(end != string::npos)
	{
		end=cmd.find(' ');
		v.push_back(cmd.substr(begin,end-begin));
		cmd=cmd.substr(end+1,cmd.size()-end-1);
	}
	runShell(v);
}


int main()
{
	string tip ="[minishell]$ ";
	//getchar();
	//fflush(stdin);
	string cmd;
	vector<string> vcmd;
	while(1)
	{
		cout<<tip;
		getline(cin,cmd);
		transStr(cmd);
	}

	return 0;
}
