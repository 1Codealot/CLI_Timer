#include <iostream>
#include "scrambles.cpp"

using namespace std;

float inputtedTime;

int main(int argc, char const *argv[])
{
	if (argc == 1)
	{
		cout<<"You fogor commands lul.";
	}
	srand(static_cast<unsigned>(time(NULL)));
	if (*argv[1] == '3')
	{
		while(*argv[2] == 'c'){
		cout<<Three_By_Three();
		cin>>inputtedTime;
		}
	}
	else if (*argv[1] == '2')
	{
		while(*argv[2] == 'c'){
			cout<<Two_By_Two();
			cin>>inputtedTime;
		}
	}
	else if (*argv[1] == '4')
	{
		while(*argv[2] == 'c'){
			cout<<Four_By_Four();
			cin>>inputtedTime;
		}
	}
	else if (*argv[1] == '5')
	{
		while(*argv[2] == 'c'){
			cout<<Five_By_Five();
			cin>>inputtedTime;
		}
	}
	else if (*argv[1] == '6')
	{
		while(*argv[2] == 'c'){
			cout<<Six_By_Six();
			cin>>inputtedTime;
		}
	}
	else if (*argv[1] == '7')
	{
		while(*argv[2] == 'c'){
			cout<<Seven_By_Seven();
			cin>>inputtedTime;
		}
	}
	return 0;
}