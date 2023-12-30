#pragma once
#include <string>
#include <cmath>

inline float timeStrToFloatSecs(std::string time_in)
{

    size_t pos = time_in.find('.');

    // Removed as it was more buggy than not.
    // TODO: Actually make it work

    // if (pos != time_in.length() - 3){ // Fix to edge case when a user put in something like 1.1 where it would say 0.11 instead of 1.1(0)
    //     time_in.append("0");
    // }

    while (pos != std::string::npos)
    {
        time_in.erase(pos, 1);
        pos = time_in.find('.');
    }

    pos = time_in.find(':');

    while (pos != std::string::npos)
    {
        time_in.erase(pos, 1);
        pos = time_in.find(':');
    }

    time_in.insert(0, 8 - time_in.length(), '0');

    int HMSD[]{-1, -1, -1, -1}; // HHMMSSDD

    int part{0};

    /*
     * Imagine 00000001
     * HMSD[0] = 00 (at(0) and at(1))
     * HMSD[1] = 00 (at(2) and at(3))
     * HMSD[2] = 00 (at(4) and at(5))
     * HMSD[3] = 01 (at(6) and at(7))
     */

    for (int i = 0; i <= 6; i += 2)
    {
        const int digit1 = std::stoi(std::string(1, time_in.at(i))) * 10;
        const int digit2 = std::stoi(std::string(1, time_in.at(i + 1)));
        const int asdf = digit1 + digit2;
        HMSD[part] = asdf;

        part++;
    }

    // Now onto floating

    HMSD[1] += HMSD[0] * 60;
    HMSD[2] += HMSD[1] * 60;

    return static_cast<float>(HMSD[2]) + static_cast<float>(HMSD[3]) / 100;
}

inline std::string outputTime(std::string time_in)
{
    size_t pos = time_in.find('.');

    while (pos != std::string::npos)
    {
        time_in.erase(pos, 1);
        pos = time_in.find('.');
    }

    pos = time_in.find(':');

    while (pos != std::string::npos)
    {
        time_in.erase(pos, 1);
        pos = time_in.find(':');
    }

    time_in.insert(0, 8 - time_in.length(), '0');

    time_in.insert(2, ":");
    time_in.insert(5, ":");
    time_in.insert(8, ".");

    // sigfigs

    while (time_in.at(0) == '0' && time_in.at(1) == '0' && time_in.at(2) != '.')
    {
        time_in.erase(0, 3);
    }

    if (time_in.at(0) == '0')
    {
        time_in.erase(0, 1);
    }

    return time_in;
}

inline std::string outputTimePretty(float time_in_seconds)
{
    std::string output{""};
    
    // Thanks: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/c-programming-basic-exercises-17.php

    int hours = time_in_seconds / 3600;
    int minutes =  (time_in_seconds -(3600*hours)) / 60;
    float seconds = time_in_seconds - (3600*hours) - (60*minutes);

    //Make seconds to 2 decimal places    

    std::string seconds_str = std::to_string(seconds);
    seconds_str = seconds_str.substr(0, seconds_str.find(".") + 3);

    // Actually outputting
    output += std::to_string(hours);
    output += ":";

    if (minutes < 10){
        output += "0";
    }
    output += std::to_string(minutes);
    output += ":";

    if (seconds < 10){
        output += "0";
    }

    output += seconds_str;

    if(seconds_str.length() == 3){
        output += "0";
    }

    return output;
}

// inline std::string outputTimePretty(std::string time_in){
//     return outputTimePretty(timeStrToFloatSecs(time_in));
// }