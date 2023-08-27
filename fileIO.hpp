#include <string>
#include <filesystem>

std::string getPath(){
    // TODO: Add cases to non-windows eventually.
    std::string appDataPath = std::getenv("APPDATA");
    std::string targetDir = appDataPath + "\\CLI_Timer_Sessions\\";

    std::filesystem::create_directory(targetDir);

    return targetDir;
}


std::string changeExtensionAndAddPath(std::string fileName){
   std::string finalFileName;
    for(int i = 2; i < fileName.length(); i++){ // Starts at index 2 because of -s.
        if (fileName[i] == '.'){
            break;
        }
        else{
            finalFileName += fileName[i];
        }
    }
    return getPath() + finalFileName + ".CLI_T_S"; // CLI_T_S means CLI Timer Session.
}

void save_to_file(std::string sessionName, std::string scramble, float time, std::string penalty, std::string comment){
    FILE *fptr;
    fptr = fopen(changeExtensionAndAddPath(sessionName).c_str(), "a");

    if (penalty == "DNF" || penalty == "dnf")
    {
        fprintf(fptr, "%s;DNF(%.2f);%s;\n", scramble.c_str(), time, comment.c_str());
    } else if (penalty == "+2")
    {
        fprintf(fptr, "%s;%.2f+;%s;\n", scramble.c_str(), time+2, comment.c_str());
    } else
    {
        fprintf(fptr, "%s;%.2f;%s;\n", scramble.c_str(), time, comment.c_str());
    }
    fclose(fptr);
}