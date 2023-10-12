#include <string>

float timeStrToFloatSecs(std::string time_in){

    size_t pos = time_in.find('.');

    while (pos != std::string::npos){
        time_in.erase(pos, 1);
        pos = time_in.find('.');
    }


    pos = time_in.find(':');

    while (pos != std::string::npos){
        time_in.erase(pos, 1);
        pos = time_in.find(':');
    }

    time_in.insert(0, 8-time_in.length(), '0');

    
    int HMSD[] {-1, -1, -1, -1}; //HHMMSSDD
                                                                 
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
    size_t pos = time_in.find('.');

    while (pos != std::string::npos){
        time_in.erase(pos, 1);
        pos = time_in.find('.');
    }


    pos = time_in.find(':');

    while (pos != std::string::npos){
        time_in.erase(pos, 1);
        pos = time_in.find(':');
    }

    time_in.insert(0, 8-time_in.length(), '0');

    time_in.insert(2, ":");
    time_in.insert(5, ":");
    time_in.insert(8, ".");

    // sigfigs

    while (time_in.at(0) == '0' && time_in.at(1) == '0' && time_in.at(2) != '.'){
        time_in.erase(0, 3);
    }

    if (time_in.at(0) == '0'){
        time_in.erase(0, 1);
    }

    return time_in;
}
