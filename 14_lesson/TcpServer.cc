#include"Select.hpp"

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		cout<<"Usage:"<<argv[0]<<" port"<<endl;
		exit(1);
	}
	SelectServer *ssp = new SelectServer(atoi(argv[1]));
	ssp->InitServer();
	ssp->Run();
	
	delete ssp;
	return 0;
}
