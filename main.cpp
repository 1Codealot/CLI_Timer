#include <iostream>

#include "Scrambles.hpp"
#include "fileIO.hpp"

using namespace std;

float inputtedTime;

// Commandline stuff. Move later

bool shouldSave(int argc, const char *argv[])
{
	if (argc < 3)
	{
		return false;
	}
	else
	{
		return (argv[2][0] == '-' && argv[2][1] == 's');
	}
}

bool shouldContinue(int argc, const char *argv[])
{
	if (argc < 3)
	{
		return false;
	}
	else
	{
		return (argv[2][0] == 'c' || shouldSave(argc, argv));
	}
}

bool shouldPrompt(int argc, const char *argv[])
{
	if (argc < 4)
	{ // --no_prompt should be 4th opt
		return true;
	}
	else
	{
		if (argv[3][0] == '-' && argv[3][1] == '-' && argv[3][2] == 'n' && argv[3][3] == 'o' && argv[3][4] == '_' && argv[3][5] == 'p' && argv[3][6] == 'r' && argv[3][7] == 'o' && argv[3][8] == 'm' && argv[3][9] == 'p' && argv[3][10] == 't')
		{
			if (shouldSave(argc, argv))
			{
				cout << "You can't save without prompting therefore it will prompt\n";
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}

// Prompting
float getTime(){
	float inputtedTime;
	string correct;

	cout << "\nEnter your time: ";
	cin >> inputtedTime;

	cout << "\nYou entered in " << fixed << setprecision(2) << inputtedTime << "\nIs this correct? (Y/n)\n";

	cin.ignore();

	getline(cin, correct);

	if (correct.length() == 0)
	{
		return inputtedTime;
	}
	else if (correct[0] == 'Y' || correct[0] == 'y') // bruh
	{
		return inputtedTime;
	}
	else
	{
		return getTime();
	}
}

string getPenalty(){
	string penalty;

	cout << "Enter an penalty (OK/+2/dnf)\n";
	getline(cin, penalty);

	if (penalty.length() == 0)
	{
		return "OK";
	}
	else if (penalty == "OK" || penalty == "ok" || penalty == "+2" || penalty == "DNF" || penalty == "dnf")
	{
		return penalty;
	}
	else
	{
		return getPenalty();
	}
}


int main(int argc, char const *argv[])
{

	if (argc == 1)
	{
		cerr << "You fogor commands lul.";
		return 1;
	}

	const bool prompt = shouldPrompt(argc, argv);
	const bool save = shouldSave(argc, argv);
	const bool cont = shouldContinue(argc, argv);

	srand(static_cast<unsigned>(time(nullptr)));

	do
	{ // while (cont);
		string currentScramble = /*Lots of spaces btw*/ "                                                                                                                           ";
		// Get scramble

		currentScramble = generate_scramble(*argv[1]);

		// Edge case incase idot uses this intellecktualy maid sw.
		if (currentScramble == "Unknown puzzle")
		{
			cerr<<"Unknown puzzle type: "<<*argv[1];
			exit(EXIT_FAILURE);
		}

		cout << currentScramble;

		if (!prompt)
		{
			string buffer;
			getline(cin, buffer);
			continue;
		}

		else
		{
			float solveTime = getTime();			

			string penalty = getPenalty();

			if (save)
			{
				string comment;
				cout << "Enter in a comment (or don't you can leave blank)\n";
				cin.ignore();
				getline(cin, comment);

				save_to_file(argv[2], currentScramble, solveTime, penalty, comment);
			}
		}
	} while (cont);

	return 0;
}