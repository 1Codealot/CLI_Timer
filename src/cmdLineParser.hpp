#include <iostream>
#include <string>

#define cmdLineArgs int argc, const char *argv[]

struct should{
    char cubeType;
    bool shouldSave;
    std::string fileName;
    bool shouldContinue;
    bool shouldPrompt;
};

char getCubeType(cmdLineArgs){
    if(argc == 1){
        std::cout<<"You need a cube type.";
        exit(EXIT_FAILURE);
    } else {
        // Go through all the argv finding a  1 length single char
        for (int i = 1; i < argc; ++i) {
            // I could do some magic ASCII checking (i.e. if (*argv[i]) is between ASCII nums for '2' to '7')
            // However that wouldn't make much sense
            // Although c++ isn't meant to be understood easily
            if ((*argv[i] == '2' || *argv[i] == '3' || *argv[i] == '4' || *argv[i] == '5' || *argv[i] == '6' || *argv[i] == '7' || *argv[i] == 'P' || *argv[i] == 'M' || *argv[i] == 'S' || *argv[i] == 'C') && (*argv[i] != 'c')) {
                return *argv[i];
            }
        }
        std::cout<<"Cube type not found.";
        exit(EXIT_FAILURE);
    }
}

bool shouldSave(cmdLineArgs){
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-' && argv[i][1] == 's'){
            return true;
        }
    }
    return false;
}

std::string getFileName(cmdLineArgs){
    if (shouldSave(argc, argv)) {
        // Find the file.
        for (int i = 1; i < argc; ++i){
            if (argv[i][0] == '-' && argv[i][1] == 's'){
                std::string fileName = std::string(argv[i]);
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

bool shouldContinue(cmdLineArgs){
    if (shouldSave(argc, argv))
    {
        return true;
    }
    
    // Oops, turned on python mode. lmao
    for (int i = 1; i < argc; ++i)
        if (*argv[i] == 'c')
            return true;

    return false;
}

bool shouldPrompt(cmdLineArgs){
    for (int i = 1; i < argc; ++i)
        if (std::string(argv[i]) == "--no_prompt"){
            if (shouldSave(argc, argv)){
                std::cout<<"You are saving to a file; this means you will need prompting; therefore you will be prompted.\nHowever you can type 'save' if you do want to save to a file with `--no_prompt`"<<std::endl;
                return true;
            } else {
                return false;
            }
        }
    return true;
}

void setup(struct should &Options, cmdLineArgs){
    // Pre-checks
    // These are for like `help` or `--version`

    std::string helpMSG = "How to use CLI_Timer.\nCLI_Timer (cube type) [c] | [-s{session name}] | [--no_prompt]\
    \n\nArgument (cube type) means an NxN of (2)x2 (3)x3 to (7)x7 or (S)kewb, (P)yraminx, (M)egaminx, or (C)lock.\
    It is required (why else would you use it?)\n\n[c] means [c]ontinuous, meaning it won't stop after generating one scramble\
    \n\nArgument [-s] is for saving to a file which name will come directly after [-s] (e.g. CLI_Timer 3 -s3x3_One_Handed)\
    \nIt will save to a .CLI_T_S (CLI_Timer_Session) file. Check README.md to see where it goes on your OS.\
    \n\nArgument [--no_prompt] will just generate a scramble, not ask for a time (for this reason you can't have [-s] with this), wait for an enter, then generate another one.\
    \nAlthough you can type in 'save' if you really want to save that time.\
    \n\nCLI_Timer (--version)\nOutputs the current version of CLI_Timer\n\nCLI_Timer (help)\nOutputs this.\
    \n\nAny issues, put them on the GitHub repo.";

    if (argc == 1){
        std::cout<<helpMSG<<std::endl;
        exit(EXIT_SUCCESS);
    } else if (std::string(argv[1]) == "help") {
        std::cout<<helpMSG<<std::endl;
        exit(EXIT_SUCCESS);
    } else if (std::string(argv[1]) == "--version"){
        std::cout<<"CLI_Timer version: 1.9.3\n\n";
        std::cout<<"Changes: Made it possible to save to a file with `--no_prompt` by typing 'save'"<<std::endl;
        std::cout<< "This required changing how file name was 'calculated'" <<std::endl;
        exit(EXIT_SUCCESS);
    }

    Options.cubeType = getCubeType(argc, argv);
    Options.shouldSave = shouldSave(argc, argv);
    Options.fileName = getFileName(argc, argv);
    Options.shouldContinue = shouldContinue(argc, argv);
    Options.shouldPrompt = shouldPrompt(argc, argv);
}
