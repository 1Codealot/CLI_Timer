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
            if ((*argv[i] == '2' || *argv[i] == '3' || *argv[i] == '4' || *argv[i] == '5' || *argv[i] == '6' || *argv[i] == '7' || *argv[i] == 'P' || *argv[i] == 'M' || *argv[i] == 'S' || *argv[i] == 'K') && (*argv[i] != 'c')) {
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
                    return fileName.substr(2, fileName.length());
                }
            }
        }
    } 
    return "";
}

bool shouldContinue(cmdLineArgs){
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
                std::cout<<"You are saving to a file; this means you will need prompting; therefore you will be prompted."<<std::endl;
                return true;
            } else {
                return false;
            }
        }
    return true;
}

void setup(struct should &Options, cmdLineArgs){
    Options.cubeType = getCubeType(argc, argv);
    Options.shouldSave = shouldSave(argc, argv);
    Options.fileName = getFileName(argc, argv);
    Options.shouldContinue = shouldContinue(argc, argv);
    Options.shouldPrompt = shouldPrompt(argc, argv);
}
