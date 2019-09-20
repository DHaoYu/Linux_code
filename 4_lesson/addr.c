#include<stdio.h>

int g_val=1;
int g-noval;
int main()
{
	printf("main:       %d\n",main);
	printf("readonly    %d\n","123");
	
	printf("init        %d\n",&g_val);
	printf("uninit      %d\n",&g_noval);
	int* arr = (int)malloc(sizeof(20));
	printf("heap        %d\n",&arr);	
	printf("stack       %d\n",arr);
	printf("env         %d\n",&env);		
		
	return 0;
}
