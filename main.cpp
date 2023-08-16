#include <iostream>
#include "Scrambles.hpp"
#include "fileIO.hpp"

using namespace std;

float inputtedTime;

int main(int argc, char const *argv[])
{

	const bool shouldContinue = (argv[2][0] == 'c' || (argv[2][0] == '-' && argv[2][1] == 's'));
	if (argc == 1)
	{
		cout<<"You fogor commands lul.";
		return 1;
	}

	srand(static_cast<unsigned>(time(NULL)));

	if (*argv[1] == '3')
		{
		do
			{
				string currentScramble = Three_By_Three();
				cout<<currentScramble<<"\nEnter your time: ";
				cin>>inputtedTime;
				save(argv[2], currentScramble, inputtedTime);
			} while (shouldContinue);	}

	else if(*argv[1] == '2')
		{
		do
			{
				string currentScramble = Two_By_Two();
				cout<<currentScramble<<"\nEnter your time: ";
				cin>>inputtedTime;
				save(argv[2], currentScramble, inputtedTime);
			} while (shouldContinue);	}

	else if(*argv[1] == '4')
		{
		do
			{
				string currentScramble = Four_By_Four();
				cout<<currentScramble<<"\nEnter your time: ";
				cin>>inputtedTime;
				save(argv[2], currentScramble, inputtedTime);
			} while (shouldContinue);	}

	else if(*argv[1] == '5')
		{
		do
			{
				string currentScramble = Five_By_Five();
				cout<<currentScramble<<"\nEnter your time: ";
				cin>>inputtedTime;
				save(argv[2], currentScramble, inputtedTime);
			} while (shouldContinue);	}

	else if(*argv[1] == '6')
		{
		do
			{
				string currentScramble = Six_By_Six();
				cout<<currentScramble<<"\nEnter your time: ";
				cin>>inputtedTime;
				save(argv[2], currentScramble, inputtedTime);
			} while (shouldContinue);	}

	else if(*argv[1] == '7')
		{
		do
			{
				string currentScramble = Seven_By_Seven();
				cout<<currentScramble<<"\nEnter your time: ";
				cin>>inputtedTime;
				save(argv[2], currentScramble, inputtedTime);
			} while (shouldContinue);	}

	else if(*argv[1] == 'S')
		{
		do
			{
				string currentScramble = Skewb();
				cout<<currentScramble<<"\nEnter your time: ";
				cin>>inputtedTime;
				save(argv[2], currentScramble, inputtedTime);
			} while (shouldContinue);	}

	else if(*argv[1] == 'M')
		{
		do
			{
				string currentScramble = Megaminx();
				cout<<currentScramble<<"\nEnter your time: ";
				cin>>inputtedTime;
				save(argv[2], currentScramble, inputtedTime);
			} while (shouldContinue);	}

	else if(*argv[1] == 'P')
		{
		do
			{
				string currentScramble = Pyraminx();
				cout<<currentScramble<<"\nEnter your time: ";
				cin>>inputtedTime;
				save(argv[2], currentScramble, inputtedTime);
			} while (shouldContinue);	}

	else if(*argv[1] == 'K')
		{
		do
			{
				string currentScramble = Clock();
				cout<<currentScramble<<"\nEnter your time: ";
				cin>>inputtedTime;
				save(argv[2], currentScramble, inputtedTime);
			} while (shouldContinue);	}

	return 0;
}