#include <iostream>
#include "Scrambles.hpp"
#include "fileIO.hpp"

using namespace std;

float inputtedTime;

bool shouldSave(int argc, const char *argv[]){
	if (argc != 3){
		return false;
	}else{
		return (argv[2][0] == '-' && argv[2][1] == 's');
	}
}

bool shouldContinue(int argc, const char *argv[]){
	if (argc != 3){
		return false;
	}else{
		return (argv[2][0] == 'c' || shouldSave(argc, argv)); 
	}
}

int main(int argc, char const *argv[])
{

	if (argc == 1)
	{
		cerr<<"You fogor commands lul.";
		return 1;
	}

    const bool save = shouldSave(argc, argv);
    const bool cont = shouldContinue(argc, argv);

	srand(static_cast<unsigned>(time(NULL)));


	do
	{
		string currentScramble;
		// Get scramble
		switch (*argv[1])
		{
		case '2':
			currentScramble = Two_By_Two();
			break;

		case '3':
			currentScramble = Three_By_Three();
			break;

		case '4':
			currentScramble = Four_By_Four();
			break;

		case '5':
			currentScramble = Five_By_Five();
			break;
	
		case '6':
			currentScramble = Six_By_Six();
			break;

		case '7':
			currentScramble = Seven_By_Seven();
			break;

		case 'S':
			currentScramble = Skewb();
			break;

		case 'P':
			currentScramble = Pyraminx();
			break;

		case 'M':
			currentScramble = Megaminx();
			break;

		case 'K':
			currentScramble = Clock();
			break;
		
		default:
			cerr<<"Command: \""<<*argv[1]<<"\" Not understood.";
			exit(EXIT_FAILURE);
			break;
		}

		cout<<currentScramble<<"\nEnter your time: ";
 			cin>>inputtedTime;

 			if (save){
 				save_to_file(argv[2], currentScramble, inputtedTime);
 				}
				
	} while (cont);


	return 0;
}
