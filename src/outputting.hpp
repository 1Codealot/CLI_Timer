#pragma once
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
    \n\nLICENCES: Main: MIT licences.\nSquare-1 code: GNU General Public License v3.0 (repo: <https://github.com/thewca/tnoodle-lib>)";
}

void outputVersion()
{
	std::cout << "CLI_Timer version: 1.14\n\n";
    std::cout << "Scramble outputs ⅓ of the screen + avg to right" << std::endl;
	std::cout << "Moved the outputting code to another file." << std::endl;
}