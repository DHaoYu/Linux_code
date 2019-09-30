#include<iostream>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

void* thread_routine(void* arg)
{
	while(1)
	{
	cout<<"i am a new thread!"<<(char*)arg<<endl;
	sleep(1);
	}
}

int main()
{
	pthread_t thr;
	pthread_create(&thr,NULL,thread_routine,(void*)"thread 1");
	sleep(3);
	cout<<"i am main thread "<<endl;
	cout<<(pthread_t*)thr<<endl;
	return 0;
}
