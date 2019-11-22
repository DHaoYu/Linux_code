#include<iostream>
using namespace std;

struct test{
	long a;
	short b;
	int c;
	int* d;
};

int main()
{
	cout<<sizeof(long)<<endl;
	cout<<sizeof(short)<<endl;
	cout<<sizeof(int)<<endl;
	cout<<sizeof(int*)<<endl;
	cout<<sizeof(test)<<endl;
}
