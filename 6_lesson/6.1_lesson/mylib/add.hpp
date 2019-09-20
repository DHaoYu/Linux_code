#include<iostream>
using namespace std;

template<class T>
int add(T& left,T& right);


template<class T>
int add(T& left,T& right)
{
	cout<<"add ranning> > >";
	return left+right;
}

