#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

static std::string getPath()
{
#ifdef _WIN32
    std::string appDataPath = std::getenv("%%APPDATA%");
    std::string targetDir = appDataPath + "\\CLI_Timer_Sessions\\";
    std::filesystem::create_directory(targetDir);

#elif __APPLE__
    std::string appDataPath = std::getenv("HOME");
    std::string targetDir = appDataPath + "/Library/Application Support/CLI_Timer_Sessions/";
    std::filesystem::create_directory(targetDir);

#elif __linux__
    std::string appDataPath = std::getenv("HOME");
    std::string targetDir = appDataPath + "/.config/CLI_Timer_Sessions/";
    std::filesystem::create_directory(targetDir);

#else
    return "./CLI_Timer_Sessions/";

#endif
    return targetDir;
}

static std::string changeExtensionAndAddPath(std::string fileName)
{
    // This is incase someone saves while doing `--no_prompt`
    long unsigned int index = 0;
    
    if (fileName[0] == '-' && fileName[1] == 's'){
        index += 2;
    }

    std::string finalFileName;
    for (; index < fileName.length(); index++)
    { 
        if (fileName[index] == '.')
        {
            break;
        }
        else
        {
            finalFileName += fileName[index];
        }
    }
    return getPath() + finalFileName + ".CLI_T_S"; // CLI_T_S means CLI Timer Session.
}

inline void save_to_file(std::string sessionName, const std::string& scramble, const float time, const std::string& penalty, const std::string& comment) {
    std::ofstream fileToSaveTo(changeExtensionAndAddPath(std::move(sessionName)), std::fstream::app);

    if (penalty == "DNF" || penalty == "dnf"){
        fileToSaveTo<<scramble<<"§DNF("<<std::fixed<<std::setprecision(2)<<time<<")~"<<comment<<std::endl;
    }
    else if (penalty == "+2")
    {
        fileToSaveTo<<scramble<<"§"<<std::fixed<<std::setprecision(2)<<(time+2)<<"+~"<<comment<<std::endl;
    }
    else
    {
        fileToSaveTo<<scramble<<"§"<<std::fixed<<std::setprecision(2)<<time<<"~"<<comment<<std::endl;
    }

    fileToSaveTo.close();

}

inline float calculateAvg(std::string fileName){

    fileName = changeExtensionAndAddPath(fileName);

    float total = 0;
    unsigned int lines = 0;

    std::string currLine;

    std::ifstream sessionFile(fileName);

    while (getline(sessionFile, currLine))
    {
        // Find time
        
        std::string timeSubStr = 
            currLine.substr(
                currLine.find("§") + 2, 
                (currLine.find('~') + 2) - (currLine.find("§") + 2) - 2
        );

        total += std::stof(timeSubStr);

        lines++;
    }
    if (lines == 0) return 0.0f;

    return total / lines;

}

inline float calculateAvg(const std::vector<float>& times){
   if (times.empty()) return 0.0f;

    float total = 0;

    for (const float currTime : times)
    {
        total += currTime;
    }

    return total / times.size();

}
