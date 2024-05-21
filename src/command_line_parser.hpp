#pragma once
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "outputting.hpp"

#define cmdLineArgs int argc, const char *argv[]

struct BLD
{
    bool on;
    int count;
};

struct should
{
    char cubeType;
    bool shouldSave;
    std::string fileName;
    bool shouldContinue;
    bool shouldPrompt;
    int scrambleCount;
    bool shouldShowAvg;
    bool needEnter;
    struct BLD blindfolded;
    bool fmc;
    bool shouldFormat;
    size_t cache_size;
    long seed;
};

static char getCubeType(std::vector<std::string> &args)
{
    // Go through all the argv finding a  1 length single char
    for (auto &arg : args)
    {
        switch (arg.at(0))
        {
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case 'P':
        case 'M':
        case 'S':
        case 'C':
        case 'Q':
            return arg.at(0);
        default:
            break;
        }
    }
    std::cout << "Cube type not found.";
    exit(EXIT_FAILURE);
}

static bool shouldSave(std::vector<std::string> &args)
{
    for (const auto &arg : args)
    {
        if (arg.substr(0, 2) == "-s")
        {
            return true;
        }
    }
    return false;
}

static std::string getFileName(std::vector<std::string> &args)
{
    if (shouldSave(args))
    {
        // Find the file.
        for (const auto &arg : args)
        {
            if (arg.substr(0, 2) == "-s")
            {
                std::string fileName = arg;
                if (fileName.length() <= 2)
                {
                    std::cerr << "You tried to save to a file but you didn't give it a name\n\n";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    return fileName;
                }
            }
        }
    }
    return "";
}

static int getCount(std::vector<std::string> &args)
{
    for (const auto &currArg : args)
    {
        if (currArg.substr(0, 7) == "--count")
        {
            return std::stoi(currArg.substr(7, currArg.size()));
        }
    }
    return -1;
}

static bool shouldContinue(std::vector<std::string> &args)
{
    if (shouldSave(args) || getCount(args) >= 1)
    {
        return true;
    }

    // Oops, turned on python mode. lmao
    for (const auto &arg : args)
        if (arg == "c")
            return true;

    return false;
}

static bool shouldPrompt(std::vector<std::string> &args)
{
    for (size_t i = 0; i < args.size(); ++i)
        if (args.at(i) == "--no_prompt")
        {
            if (shouldSave(args))
            {
                std::cout << "You are saving to a file; this means you will need prompting; therefore you will be prompted.\nHowever you can type 'save' if you do want to save to a file with `--no_prompt`" << std::endl;
                return true;
            }
            else
            {
                return false;
            }
        }
    return true;
}

static bool shouldShowAvg(std::vector<std::string> &args)
{
    for (const auto &arg : args)
    {
        if (arg == "--no_avg" || arg == "--no_prompt")
        {
            return false;
        }
    }
    return true;
}

static bool needEnter(std::vector<std::string> &args)
{
    for (size_t i = 0; i < args.size(); i++)
    {
        if (args.at(i) == "--no_enter")
        {
            // This is *very* bad. oops.
            if (shouldPrompt(args) || (getCount(args) < 1))
            {
                std::cout << "Enter is needed for prompting or unlimited number of scrambles\n";
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

// TODO: Use more often!
std::string to_uppercase(std::string str)
{
    std::string out;
    for (char c : str)
    {
        if (std::islower(c))
        {
            out += std::toupper(c);
        }
        else
        {
            out += c;
        }
    }
    return out;
}

static struct BLD blindfolded(std::vector<std::string> &args)
{
    for (size_t i = 0; i < args.size(); i++)
    {
        if (args.at(i) == "-b" || args.at(i) == "-B")
        {
            if (getCubeType(args) == '3' || getCubeType(args) == '4' || getCubeType(args) == '5')
            {
                return {
                    .on = true,
                    .count = 1};
            }
            else
            {
                std::cout << "No blindfolded support for cubes that aren't 3x3 or 4x4 or 5x5.\n";
                return {
                    .on = false,
                    .count = 0};
            }
        }
        else if (to_uppercase(args.at(i).substr(0, 5)) == "-MBLD")
        {
            if (getCubeType(args) == '3')
            {
                return {
                    .on = true,
                    .count = std::stoi(args.at(i).substr(5))};
            }
            else
            {
                std::cout << "Multiblind support is only for 3x3\nAlso you are insane for doing it on non 3x3s\n";
                return {
                    .on = false,
                    .count = 0};
            }
        }
    }
    return {
        .on = false,
        .count = 0};
}

static bool fmc(std::vector<std::string> &args)
{
    for (size_t i = 0; i < args.size(); i++)
    {
        if (args.at(i).substr(0, 2) == "-f" || args.at(i).substr(0, 2) == "-F")
        {
            if (getCubeType(args) == '3')
            {
                if (!blindfolded(args).on)
                {
                    return true;
                }
                else
                {
                    std::cout << "Incompatible arguments: -f cannot be used with non-blindfolded cubes.\n";
                    return false;
                }
            }
            else
            {
                std::cout << "Incompatible arguments: -f can only be used with 3x3 cubes.\n";
                return false;
            }
        }
    }
    return false;
}

static bool shouldFormat(std::vector<std::string> &args)
{
    for (size_t i = 0; i < args.size(); i++)
    {
        if (args.at(i) == "--no_format")
        {
            return false;
        }
    }
    return true;
}

static size_t getCacheSize(std::vector<std::string> &args)
{
    for (size_t i = 0; i < args.size(); i++)
    {
        if (args.at(i).substr(0, 12) == "--cache_size")
        {
            return std::stoi(args.at(i).substr(12, args.at(i).size()));
        }
    }
    return 50; // Cache size of 50 by default
}

static long getSeed(std::vector<std::string> &args)
{
    std::string seed_flag;
    bool hasNonNum = false;

    for (const std::string &arg : args)
    {
        if (arg.substr(0, 6) == "--seed")
        {
            seed_flag = arg;
        }
    }

    if (seed_flag.empty())
    {
        return -1;
    }

    std::string seed;
    for (char c : seed_flag.substr(6))
    {
        if ('0' <= c && c <= '9')
        {
            seed += c;
        }
        else
        { // This adds the ASCII num of `c` as a string
            seed += std::to_string(c);
            hasNonNum = true;
        }
    }

    long actual = std::stol(seed);

    if (hasNonNum)
    {
        std::clog << "WARNING: Seed has non-numeric values (including \"-\").\nIt has been coverted to: " << actual << ".\n";
    }

    return actual;
}

inline void setup(struct should &Options, cmdLineArgs)
{
    // Pre-checks
    // These are for like `help` or `--version`

    // this will make everything easier
    std::vector<std::string> arguments;

    // init vector
    for (int i = 1; i != argc; i++)
    {
        arguments.emplace_back(argv[i]);
    }

    if (argc == 1)
    {
        outputHelp();
        exit(EXIT_SUCCESS);
    }
    else if (arguments.at(0) == "help")
    {
        outputHelp();
        exit(EXIT_SUCCESS);
    }
    else if (arguments.at(0) == "--version")
    {
        outputVersion();
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
    Options.blindfolded = blindfolded(arguments);
    Options.fmc = fmc(arguments);
    Options.shouldFormat = shouldFormat(arguments);
    Options.cache_size = getCacheSize(arguments);
    Options.seed = getSeed(arguments);
}
