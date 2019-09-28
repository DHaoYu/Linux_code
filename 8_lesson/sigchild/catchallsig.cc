#include<iostream>
#include<signal.h>
#include<unistd.h>

using namespace std;

void handler(int sig)
{
	cout<<"catch signal "<<sig<<endl;
}

int main()
{
	size_t i = 1;
	while(i<=31)
	{
		signal(i,handler);
		i++;
	}

	while(1)
	{
		cout<<"catching signal...\n"<<endl;
		sleep(1);
	}

	return 0;
}
