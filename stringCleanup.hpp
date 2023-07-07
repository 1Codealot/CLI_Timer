#include <string>

std::string strCleanup(std::string str){
    std::string final;
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
        case ' ': // Not clock stuff
        case '\'': // :(
            final+=x;
            break;


        default:
            continue;
        }
    }
    return final;
}