#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>

#define MYPATH "."
#define PROJ_ID 0x6666

int main()
{
	key_t key = ftok(MYPATH,PROJ_ID);
	if(key < 0)
	{
		perror("ftok");
		exit(1);
	}
	int shmid = shmget(key,1024,IPC_CREAT|IPC_EXCL|0664);
	if(shmid < 0)
	{
		perror("shmget");
		exit(1);
	}
	char* mes = shmat(shmid,NULL,0);
//	int i='A';
	while(1)
	{
		printf("server#: %s\n",mes);
		sleep(1);
	}
	shmdt(mes);
//	shmctl(shmid,IPC_RMID,NULL);
	
	return 0;
}
