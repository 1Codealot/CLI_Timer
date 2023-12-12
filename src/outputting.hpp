#include <vector>
#include <iostream>
#include <iomanip>
#include "TimeStrToFloat.hpp"

// Credit:
// https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns

#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

int get_terminal_width(void){
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        return columns;

    #elif __linux__
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        int columns = w.ws_col;
        return columns;

    #else
        return 30;

    #endif
}

// End credit


void output(std::string scramble, float avg)
{
	// avg must be > 0 otherwise I will not output it.

	std::vector<std::string> scrambleLines;

	int width = get_terminal_width();

	const char charToLookFor = scramble.find('/') != std::string::npos ? '/' : ' ';

	size_t startPos = 0;
	size_t endPos = 0;

	while (endPos < scramble.length())
	{
		endPos = startPos + width/3;
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

        int spaces = width - scrambleLines[0].length() - 18 - avgAsStr.length();

        scrambleLines[0] += std::string(spaces, ' ');
		scrambleLines[0] += "Current average: " + avgAsStr;
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