#include <string>

unsigned long long charCountInStr(char c, const std::string& str){
    unsigned long long count = 0;
    
    for (auto &&i : str)
    {
        if (i == c)
        {
            count++;
        }
        
    }
    return count;
}

float timeStrToFloatSecs(std::string time_in){

    if (charCountInStr('.', time_in) >= 1)
    {
        time_in.erase('.');
    }

    if (charCountInStr(':', time_in) >= 1)
    {
        time_in.erase(':');
    }

    time_in.insert(0, 8-time_in.length(), '0');

    
    int HMSD[] {-1, -1, -1, -1}; //HHMMSSDD

    //std::string in_time { "00000000" };


                                                                 
    int part { 0 };

/*
 * Imagine 00000001
 * HMSD[0] = 00 (at(0) and at(1))
 * HMSD[1] = 00 (at(2) and at(3))
 * HMSD[2] = 00 (at(4) and at(5))
 * HMSD[3] = 01 (at(6) and at(7))
 */


    for (int i = 0; i <= 6; i+=2)
    {
        int digit1 = std::stoi(std::string(1, time_in.at(i))) * 10;
        int digit2 = std::stoi(std::string(1, time_in.at(i + 1)));
        int asdf = digit1 + digit2;
        HMSD[part] = asdf;
        
        part++;
    }
    
    
    // Now onto floating


    HMSD[1] += HMSD[0]*60;
    HMSD[2] += HMSD[1]*60;

    float final_secs = (float)HMSD[2] + ((float)HMSD[3]/100);
    return final_secs;
}

std::string outputTime(std::string time_in){
    time_in.insert(0, 8-time_in.length(), '0');

    if (charCountInStr('.', time_in) >= 1)
    {
        time_in.erase('.');
    }

    if (charCountInStr(':', time_in) >= 1)
    {
        time_in.erase(':');
    }
    std::string output { time_in };

    output.insert(2, ":");
    output.insert(5, ":");
    output.insert(8, ".");

    return output;    
}

//std::string eraseTest(){
//    std::string srtyfgui { "AAAAABAAAAAAAAAC" };
//    return srtyfgui.erase('A');
//}