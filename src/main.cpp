#include "cmdLineParser.hpp"
#include "Scrambles.hpp"
#include "fileIO.hpp"
#include "TimeStrToFloat.hpp"

void output(std::string scramble, float avg)
{
	// avg must be > 0 otherwise I will not output it.

	std::vector<std::string> scrambleLines;

	constexpr int lineLen = 30;

	const char charToLookFor = scramble.find('/') != std::string::npos ? '/' : ' ';

	size_t startPos = 0;
	size_t endPos = 0;

	while (endPos < scramble.length())
	{
		endPos = startPos + lineLen;
		if (endPos >= scramble.length())
		{
			endPos = scramble.length();
		}
		else
		{
			while (endPos > startPos && scramble[endPos] != charToLookFor)
			{
				endPos--;
			}
		}
		scrambleLines.push_back((scramble.substr(startPos, endPos - startPos + (charToLookFor == '/' ? 1 : 0))));
		startPos = endPos + 1;
	}

	if (avg > 0)
	{
		// Re assign avg to 2 decimal places
		std::string avgAsStr = std::to_string(avg);
		avgAsStr = avgAsStr.substr(0, avgAsStr.find('.') + 3);

		scrambleLines[0] += "\t\t Current average: " + avgAsStr;
	}

	for (std::string &line : scrambleLines)
	{
		if (line.at(0) == ' ')
		{
			line.erase(0, 1);
		}

		std::cout << line << std::endl;
	}
}

// Prompting
float getTime()
{
	std::string inputtedTime;
	std::string correct;

	std::cout << "\nEnter your time: ";
	std::cin >> inputtedTime;

	if (inputtedTime[0] == 'Q' || inputtedTime[0] == 'q')
	{
		std::cout << std::endl;
		exit(EXIT_SUCCESS);
	}

	float real_time_secs = timeStrToFloatSecs(inputtedTime);

	std::cout << "\nYou entered in " << outputTime(inputtedTime) << " (which is also " << std::fixed << std::setprecision(2) << real_time_secs << " seconds)\nIs this correct? (Y/n)\n";

	std::cin.ignore();

	std::getline(std::cin, correct);

	if (correct.empty() || correct[0] == 'Y' || correct[0] == 'y')
	{
		return real_time_secs;
	}
	else
	{
		return getTime();
	}
}

std::string getPenalty()
{
	std::string penalty;

	std::cout << "Enter an penalty (OK/+2/dnf)\n";

	std::getline(std::cin, penalty);

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
	// Parse command line arguments
	struct should Args
	{
	};

	setup(Args, argc, argv);
	std::vector<float> timesVector;

	do
	{ // while (Args.shouldContinue);
		std::string currentScramble = generate_scramble(Args.cubeType, Args.blindfolded, Args.fmc);
		// Get scramble

		float avg = -1;

		if (Args.shouldSave)
		{
			avg = calculateAvg(Args.fileName);
			output(currentScramble, avg);
		}
		else
		{
			avg = calculateAvg(timesVector);
			output(currentScramble, calculateAvg(timesVector));
		}

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
