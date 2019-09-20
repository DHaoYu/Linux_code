#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<algorithm>

using namespace std;

void redirect(vector<string>& v)
{
	int pos = find(v.begin(),v.end(),">")-v.begin();
	static char* argv[32];
	for(size_t i=0;i<pos;i++)
		argv[i] = (char*)v[i].c_str();
	int fd = open((char*)v[pos+1].c_str(),O_CREAT|O_RDWR,0644);
	pid_t pid = fork();
	if(pid == 0)
	{
		dup2(fd,1);
		execvp((char*)v[0].c_str(),argv);
	}
	else
	{
		waitpid(pid,NULL,0);
	}
}

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
			chdir(argv[1]);// cmd: cd 
		else if(v.end()-find(v.begin(),v.end(),">"))
			redirect(v);
		else
			execvp((char*)v[0].c_str(),argv);//exec
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
