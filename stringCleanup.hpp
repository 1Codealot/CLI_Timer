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
        case 'w': // for wide moves (e.g. 4x4)
        case 'u': // Pyra tips
        case 'f':
        case 'r':
        case 'b':
        case ' ': // Not clock stuff
        case '\'': // :(
        case '\n': // Needed for megaminx
            final+=x;
            break;


        default:
            continue;
        }
    }
    // 6x6 and 7x7 should have 3Uw not U3w.
    // This should clean it
    for(int n; n!= final.length(); n++){
    	if(final[n] == '3' && final[n-1] == ' '){
    		auto holder = final[n+1];
    		final[n] = holder; final[n+1] = '3';
    		}
    	}
    return final;
}
