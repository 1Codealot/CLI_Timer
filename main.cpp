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
		do
			{
				cout<<Three_By_Three();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	else if(*argv[2] == '2')
		{
		do
			{
				cout<<Two_By_Two();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	else if(*argv[2] == '4')
		{
		do
			{
				cout<<Four_By_Four();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	else if(*argv[2] == '5')
		{
		do
			{
				cout<<Five_By_Five();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	else if(*argv[2] == '6')
		{
		do
			{
				cout<<Six_By_Six();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	else if(*argv[2] == '7')
		{
		do
			{
				cout<<Seven_By_Seven();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	return 0;
}
