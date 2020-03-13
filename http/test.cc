#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
using namespace std;

int main()
{
	
	string s = "GET /index.html HTTP/1.1";
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	cout<<s<<endl;
	//	stringstream ss(s);
//	string method, uri, version;
//	ss>>method>>uri>>version;
//	cout<<"method: "<<method<<endl;
//	cout<<"uri:    "<<uri<<endl;
//	cout<<"version:"<<version<<endl;
}
