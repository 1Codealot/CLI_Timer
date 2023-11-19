#pragma once
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#define cmdLineArgs int argc, const char *argv[]

struct should{
    char cubeType;
    bool shouldSave;
    std::string fileName;
    bool shouldContinue;
    bool shouldPrompt;
    int scrambleCount;
    bool shouldShowAvg;
    bool needEnter;
};

static char getCubeType(std::vector<std::string> &args){
    // Go through all the argv finding a  1 length single char
    for (int i = 0; i < args.size(); ++i) {
        // I could do some magic ASCII checking (i.e. if (*argv[i]) is between ASCII nums for '2' to '7')
        // However that wouldn't make much sense
        // Although c++ isn't meant to be understood easily
        if ((args.at(i) == "2" || args.at(i) == "3" || args.at(i) == "4" || args.at(i) == "5" || args.at(i) == "6" || args.at(i) == "7" || args.at(i) == "P" || args.at(i) == "M" || args.at(i) == "S" || args.at(i) == "C" || args.at(i) == "Q") && (args.at(i) != "c")) {
            return (char) args.at(i).at(0);
        }
    }
    std::cout<<"Cube type not found.";
    exit(EXIT_FAILURE);
}


static bool shouldSave(std::vector<std::string> &args){
    for (int i = 0; i < args.size(); ++i) {
       if (args.at(i).substr(0, 2) == "-s"){
	    return true;
        }
    }
    return false;
}

static std::string getFileName(std::vector<std::string> &args){
    if (shouldSave(args)) {
        // Find the file.
        for (int i = 0; i < args.size(); ++i){
            if (args.at(i).substr(0,2) == "-s"){
                std::string fileName = args.at(i);
                if (fileName.length() <= 2){
                    std::cerr<<"You tried to save to a file but you didn't give it a name\n\n";
                    exit(EXIT_FAILURE);
                } else {
                    return fileName;
                }
            }
        }
    } 
    return "";
}


static int getCount(std::vector<std::string> &args){
    for (int i = 0; i < args.size(); i++)
    {
        std::string currArg = args.at(i);
        if (currArg.substr(0, 7) == "--count")
        {
            return std::stoi(currArg.substr(7, currArg.size()));
        }
    }
    return -1;
}

static bool shouldContinue(std::vector<std::string> &args){
    if (shouldSave(args) || getCount(args) >= 1)
    {
        return true;
    }
    
    // Oops, turned on python mode. lmao
    for (int i = 0; i < args.size(); ++i)
        if (args.at(i) == "c")
            return true;

    return false;
}

static bool shouldPrompt(std::vector<std::string> &args){
    for (int i = 0; i < args.size(); ++i)
        if (args.at(i) == "--no_prompt"){
            if (shouldSave(args)){
                std::cout<<"You are saving to a file; this means you will need prompting; therefore you will be prompted.\nHowever you can type 'save' if you do want to save to a file with `--no_prompt`"<<std::endl;
                return true;
            } else {
                return false;
            }
        }
    return true;
}

static bool shouldShowAvg(std::vector<std::string> &args){
    for (int i = 0; i < args.size(); ++i){
        if (args.at(i) == "--no_avg" || args.at(i) == "--no_prompt")
        {
            return false;
        }
    }
    return true;
}

static bool needEnter(std::vector<std::string> &args){
    for (int i = 0; i < args.size(); i++)
    {
        if (args.at(i) == "--no_enter"){
            // This is *very* bad. oops.
            if(shouldPrompt(args) || (getCount(args) < 1)){
                std::cout<<"Enter is needed for prompting or unlimited number of scrambles\n";
                return true;
            } else
            {
                return false;
            }
            
        }
    }
    return true;   
}

inline void setup(struct should &Options, cmdLineArgs){
    // Pre-checks
    // These are for like `help` or `--version`

    std::string helpMSG { "How to use CLI_Timer.\nCLI_Timer (cube type) [--count{number}] [--no_enter] | [c] | [-s{session name}] | [--no_prompt] | [--no_avg] \
    \n\nArgument (cube type) means an NxN of (2)x2 (3)x3 to (7)x7 or (S)kewb, (P)yraminx, (M)egaminx, (C)lock or s(Q)uare-1.\
    It is required (why else would you use it?)\n\n[c] means [c]ontinuous, meaning it won't stop after generating one scramble.\
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
    \n\nLICENCES: Main: MIT licences.\nSquare-1 code: GNU General Public License v3.0 (repo: <https://github.com/thewca/tnoodle-lib>)" }; // Used braces so that I can fold it.

    //this will make everything easier
    std::vector<std::string> arguments;

    //init vector
    for (size_t i=1; i!=argc; i++){
        arguments.push_back(std::string(argv[i]));
    }


    if (argc == 1){
        std::cout<<helpMSG<<std::endl;
        exit(EXIT_SUCCESS);
    } else if (arguments.at(0) == "help") {
        std::cout<<helpMSG<<std::endl;
        exit(EXIT_SUCCESS);
    } else if (arguments.at(0) == "--version"){
        std::cout<<"CLI_Timer version: 1.13\n\n";
        std::cout<<"Added using a vector for the arguments."<<std::endl;
        

        exit(EXIT_SUCCESS);
    }

    Options.cubeType = getCubeType(arguments);
    Options.shouldSave = shouldSave(arguments);
    Options.fileName = getFileName(arguments);
    Options.shouldContinue = shouldContinue(arguments);
    Options.shouldPrompt = shouldPrompt(arguments);
    Options.scrambleCount = getCount(arguments);
    Options.shouldShowAvg = shouldShowAvg(arguments);
    Options.needEnter = needEnter(arguments);
}
