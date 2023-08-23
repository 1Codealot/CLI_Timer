#include <string>
#include <regex>

// 

std::string strCleanup(std::string str){
    std::string Final;
    int index = 0;
    for(char x:str){
        switch (x)
        {
        case 'U': // Obvious stuff
        case 'F':
        case 'R':
        case 'B':
        case 'L':
        case 'D':
        case '1': 
        case '2':
        case '3': // Clock stuff
        case '4':
        case '5':
        case '6':
        case 'y':
        case 'A':
        case '+':
        case '-':
        case 'w': // for wide moves (e.g. 4x4)
        case 'u': // Pyra tips
        case 'f':
        case 'r':
        case 'b':
        case ' ': // Not clock stuff
        case '\'': // :(
        case '\n': // Needed for megaminx
            break;
        default:
            continue;
        }
        index++;
    }
    // 6x6 and 7x7 should have 3Uw not U3w.
    // This should clean it
    int count = 0;
    for(auto n : Final){
        if (n == '3')
        {
            Final[count] = Final[count-1];
            Final[count-1] = '3';
            
        }
        count += 1;
    }

    return Final;
}