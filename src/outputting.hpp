#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "TimeStrToFloat.hpp"

// Credit:
// https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns

#ifdef _WIN32
    #include <windows.h>
#elif __linux__ || __APPLE__
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

    #elif __linux__ || __APPLE__
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        int columns = w.ws_col;
        return columns;

    #else
        return 30;

    #endif
}

// End credit

inline float calculateMean(std::vector<float>& times, int count=0)
{
	float avg = 0.00f;

	if (count == 0)
	{
		count = times.size();
	}

	for(float n : times)
	{
		avg += n;
	}

	avg /= (float)count;
	return avg;	
}

inline float calculateAvg(std::vector<float>& times, size_t count=0)
{
	// TODO: Check the size of times is >= count.

	int countToRemove = floor((times.size() / 10) + 1);

	if(times.size() < count)
	{
		return 0;
	}

	std::vector<float> latestTimes;

    for (size_t i = times.size() - count; i < times.size(); i++)
    {
        latestTimes.push_back(times.at(i));
    }

    std::sort(latestTimes.begin(), latestTimes.end());

	for (int i = 0; i < countToRemove; i++)
	{
		latestTimes.erase(latestTimes.begin());
		latestTimes.erase(latestTimes.end() - 1);
	}

	return calculateMean(latestTimes);
}

void appendAvg(std::vector<std::string>& scrambleLines, float avg, std::string avgName)
{
	// Smaller level = higher up.
	int level = 0;

	if (avgName == "ao5")
	{
		level = 1;
	}
	else if (avgName == "ao12")
	{
		level = 2;
	}
	else if (avgName == "ao50")
	{
		level = 3;
	}
	else if (avgName == "ao100")
	{
		level = 4;
	}

	std::string avgAsStr = std::to_string(avg);
	if(avgAsStr == "-nan"){
		avgAsStr = "0.00";
	}
	
	avgAsStr = outputTimePretty(avgAsStr.substr(0, avgAsStr.find('.') + 3));
	
	if (scrambleLines.size() < level+1)
	{
		scrambleLines.push_back("");
	}

	std::string avgText = "Current " + avgName + ": " + avgAsStr;

	int spaces = get_terminal_width() - scrambleLines.at(level).length() - avgText.length();

	scrambleLines.at(level) += std::string(spaces, ' ') + avgText;

}

void output(std::string scramble, std::vector<float>& times)
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

	float mean = calculateMean(times);
	float ao5 = calculateAvg(times, 5);
	float ao12 = calculateAvg(times, 12);
	float ao50 = calculateAvg(times, 50);
	float ao100 = calculateAvg(times, 100);
	// No need for more. If you do; just re-complie with more. lol.

	appendAvg(scrambleLines, mean, "mean");
	appendAvg(scrambleLines, ao5, "ao5");
	appendAvg(scrambleLines, ao12, "ao12");
	appendAvg(scrambleLines, ao50, "ao50");
	appendAvg(scrambleLines, ao100, "ao100");


	for (std::string &line : scrambleLines)
	{
		if(line.length() < 0){
			if (line.at(0) == ' ')
			{
				line.erase(0, 1);
			}
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

void outputHelp()
{
	std::cout << "How to use CLI_Timer.\nCLI_Timer (cube type) [-b] | [-f(mc))] [--count{number}] [--no_enter] | [c] | [-s{session name}] | [--no_prompt] | [--no_avg] \
    \n\nArgument (cube type) means an NxN of (2)x2 (3)x3 to (7)x7 or (S)kewb, (P)yraminx, (M)egaminx, (C)lock or s(Q)uare-1.\
    It is required (why else would you use it?)\n\n[c] means [c]ontinuous, meaning it won't stop after generating one scramble.\
    \n\nArgument [-b] gives scrambles for blindfolded solves for 3x3, 4x4 and 5x5 \
    \n\nArgument [-f(mc)] gives scrambles for fmc for 3x3. \
    \n--count{number} can be used to specify how many scrambles you want. Continuous is impiled. It will then quit (with code 0).\
    \n\nArgument [-s] is for saving to a file which name will come directly after [-s] (e.g. CLI_Timer 3 -s3x3_One_Handed).\
    \nIt will save to a .CLI_T_S (CLI_Timer_Session) file. Check README.md to see where it goes on your OS.\
    \nIt is also the only way to have averages displayed.\
    \n\nArgument [--no_prompt] will just generate a scramble, not ask for a time (for this reason you can't have [-s] with this), wait for an enter, then generate another one.\
    \nAlthough you can type in 'save' if you really want to save that time.\
    \nAlso you won't have averages with this.\
    \n\nArgument [--no_avg] means that it will not show the averages\
    \n\nArgument [--no_enter] will instantly output n scrambles (with the argument [--count{n}]).\
    \nYou MUST have [--no_prompt] and [--count].\
    \n\nCLI_Timer (--version)\nOutputs the current version of CLI_Timer\n\nCLI_Timer (help)\nOutputs this.\
    \n\nAny issues, put them on the GitHub repo: https://github.com/1Codealot/CLI_Timer/issues\
    \n\nLICENCES: Main: MIT licence.\nSquare-1 code: GNU General Public License v3.0 (repo: <https://github.com/thewca/tnoodle-lib>)\n";
}

void outputVersion()
{
	std::cout << "CLI_Timer version: 1.15\n\n";
    std::cout << "Changed how outputting mean works." << std::endl;
	std::cout << "Added ao5, 12, 50 and 100" << std::endl;
	std::cout << "Made outputting mean (and averages) look better" << std::endl;
}