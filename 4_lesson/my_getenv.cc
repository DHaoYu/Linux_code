#include<iostream>
#include<unistd.h>
using namespace std;

//int main(int argc,char* argv[],char* env[])
//{
//	int i=0;
//	for(;env[i];i++)
//	{
//		cout<<env[i]<<endl;
//		sleep(1);
//	}
//	return 0;
//}
//
//int main()
//{
//	extern char** environ;//env
//	int i=0;
//	for(;environ[i];i++)
//	{
//		cout<<environ[i]<<endl;
//		sleep(1);
//	}
//	return 0;
//}
//#include<stdlib.h>
//
//int main()
//{
//	cout<<getenv("PATH")<<endl;
//	return 0;	
//}
//

//#include<stdlib.h>
//int main()
//{
//	char* env = getenv("PATH");
//	if(env)
//		cout<<env<<endl;
//	else
//		cout<<"NULL"<<endl;
//	return 0;
//}

int main()
{
	printf("%s\n",getenv("PATH"));

	return 0;
}







