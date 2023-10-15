#include "cmdLineParser.hpp"
#include "Scrambles.hpp"
#include "fileIO.hpp"
#include "TimeStrToFloat.hpp"

using namespace std;

// Prompting
float getTime(){
	string inputtedTime;
	string correct;

	cout << "\nEnter your time: ";
	cin >> inputtedTime;

    if (inputtedTime[0] == 'Q' || inputtedTime[0] == 'q'){
		cout<<endl;
        exit(EXIT_SUCCESS);
    }

	float real_time_secs = timeStrToFloatSecs(inputtedTime);

	cout << "\nYou entered in " << outputTime(inputtedTime) << " (which is also " << fixed << setprecision(2) << real_time_secs << " seconds)\nIs this correct? (Y/n)\n";

	cin.ignore();

	getline(cin, correct);

	if (correct.empty() || correct[0] == 'Y' || correct[0] == 'y')
	{
		return real_time_secs;
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

	if (penalty.empty())
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

	struct should Args{};
	setup(Args, argc, argv);

	do
	{ // while (Args.shouldContinue);
		string currentScramble = generate_scramble(Args.cubeType);
		// Get scramble

		cout << currentScramble;

		if (!Args.shouldPrompt)
		{
			string buffer;
			getline(cin, buffer);
			continue;
		}

		else
		{
			float solveTime = getTime();			

			string penalty = getPenalty();

			if (Args.shouldSave)
			{
				string comment;
				cout << "Enter in a comment (or don't you can leave blank)\n";

				getline(cin, comment);
                save_to_file(Args.fileName, currentScramble, solveTime, penalty, comment);
			}
		}
	} while (Args.shouldContinue);

    return 0;
}
