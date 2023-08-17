#include <string>

std::string changeExtension(std::string fileName){
   std::string finalFileName;
    for(int i = 2; i < fileName.length(); i++){ // Starts at index 2 because of -s.
        if (fileName[i] == '.'){
            break;
        }
        else{
            finalFileName += fileName[i];
        }
    }
    return finalFileName + ".CLI_T_S"; // CLI_T_S means CLI Timer Session.
}

void save_to_file(std::string sessionName, std::string scramble, float time){
    FILE *fptr;
    fptr = fopen(changeExtension(sessionName).c_str(), "a");

    fprintf(fptr, "%s %.2f\n", scramble.c_str(), time);

    fclose(fptr);
}
