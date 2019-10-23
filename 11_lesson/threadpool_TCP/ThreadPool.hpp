#include<iostream>
#include<queue>
#include<string>
#include<pthread.h>
#include<sys/socket.h>
#include<map>
#include<unistd.h>

using namespace std;

map<string, string> dict{
	{"apple", "苹果"},
	{"banana", "香蕉"},
};

class Task{
	private:
		int fd;
	public:
		Task(int _fd):fd(_fd)
		{
		}

		Task()
		{
		}

		void Run()
		{
			char buf[1024];
			string word;
			while(1)
			{
				ssize_t s = recv(fd, buf, sizeof(buf)-1, 0);
				if(s > 0)
				{
					buf[s] = 0;
					word = buf;
				}
				else
				{
					word = "";
				}
				string value;
				auto i = dict.find(word);
				if(i != dict.end())
				{//找到了
					value = i->second;
				}
				else
				{
					value = "unknow";
				}
				send(fd, value.c_str(), value.size(), 0);
			}
			close(fd);
		}

		~Task()
		{
		}
};

class ThreadPool{
	private:
		int num;
		queue<Task> q;
		pthread_mutex_t lock;
		pthread_cond_t cond;
	public:
		ThreadPool(int num_ = 5):num(num_)
		{
			pthread_mutex_init(&lock, NULL);
			pthread_cond_init(&cond, NULL);
		
		}
		
		void PushTask(Task &t)
		{
			LockQueue();
			q.push(t);
			UnlockQueue();
			ThreadSignal();
		}

		Task PopTask()
		{
			Task t = q.front();
			q.pop();
			return t;
		}

		void LockQueue()
		{
			pthread_mutex_lock(&lock);
		}

		void UnlockQueue()
		{
			pthread_mutex_unlock(&lock);
		}
		
		bool IsEmpty()
		{
			return q.size() == 0;
		}
		
		void ThreadSignal()
		{
			pthread_cond_signal(&cond);
		}

		void ThreadWait()
		{
			pthread_cond_wait(&cond, &lock);
		}

		static	void* Routine(void *args)
		{
			ThreadPool* self = (ThreadPool*)args;
			pthread_detach(pthread_self());
			for(; ;)
			{
				self->LockQueue();
				while(self->IsEmpty())
				{
					self->ThreadWait();
				}
				Task t = self->PopTask();
				self->UnlockQueue();
				t.Run();
			}
		}
		
		void InitThreadPool()//初始化线程,产生5个线程
		{
			pthread_t tid;
			for(auto i = 0; i < num; i++)
			{
				pthread_create(&tid, NULL, Routine, (void*)this);
			}
		}
		~ThreadPool()
		{
			pthread_mutex_destroy(&lock);
			pthread_cond_destroy(&cond);
		}
};
