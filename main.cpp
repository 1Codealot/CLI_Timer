#include <iostream>
#include "Scrambles.hpp"

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

	else if(*argv[1] == '2')
		{
		do
			{
				cout<<Two_By_Two();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	else if(*argv[1] == '4')
		{
		do
			{
				cout<<Four_By_Four();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	else if(*argv[1] == '5')
		{
		do
			{
				cout<<Five_By_Five();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	else if(*argv[1] == '6')
		{
		do
			{
				cout<<Six_By_Six();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	else if(*argv[1] == '7')
		{
		do
			{
				cout<<Seven_By_Seven();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	else if(*argv[1] == 'S')
		{
		do
			{
				cout<<Skewb();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	else if(*argv[1] == 'M')
		{
		do
			{
				cout<<Megaminx();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	else if(*argv[1] == 'P')
		{
		do
			{
				cout<<Pyraminx();
				cin>>inputtedTime;
			} while (*argv[2] == 'c');	}

	return 0;
}
