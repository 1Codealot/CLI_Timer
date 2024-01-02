#include "cmdLineParser.hpp"
#include "Scrambles.hpp"
#include "fileIO.hpp"

int main(int argc, char const *argv[])
{
	// Parse command line arguments
	struct should Args
	{
	};

	setup(Args, argc, argv);
	std::vector<float> timesVector;

	do
	{ // while (Args.shouldContinue && --Args.scrambleCount != 0);

        //Populate vector from file
        if(Args.shouldSave){
            timesVector = readTimesFromFile(Args.fileName);
        }

		std::string currentScramble = generate_scramble(Args.cubeType, Args.blindfolded, Args.fmc);

		output(currentScramble, timesVector, Args.shouldShowAvg);

		if (!Args.shouldPrompt)
		{
			if (Args.needEnter)
			{
				std::string buffer;
				getline(std::cin, buffer);

				if (buffer == "Q" || buffer == "q")
				{
					exit(EXIT_SUCCESS);
				}

				else if (buffer == "save")
				{
					std::cout << "What file would you like to save to? " << std::endl;

					std::string fileName;
					getline(std::cin, fileName);

					float solveTime = getTime();

					std::string penalty = getPenalty();

					std::string comment;
					std::cout << "Enter in a comment (or don't you can leave blank)\n";

					std::getline(std::cin, comment);

					save_to_file(fileName, currentScramble, solveTime, penalty, comment);
				}
			}

			continue;
		}

		else
		{
			float solveTime = getTime();

			if (solveTime == -1)
			{
				continue;
			}

			std::string penalty = getPenalty();

			if (Args.shouldSave)
			{
				std::string comment;
				std::cout << "Enter in a comment (or don't you can leave blank)\n";

				getline(std::cin, comment);
				save_to_file(Args.fileName, currentScramble, solveTime, penalty, comment);
			}
			else
			{
				timesVector.push_back(solveTime);
			}
		}
	} while (Args.shouldContinue && --Args.scrambleCount != 0);

	return 0;
}
