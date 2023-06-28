#include <string>
#include <cstdlib>
#include <ctime>

int getRandomNum(int min, int max) {
    return rand() % (max - min) + min;
}

std::string Two_By_Two() {
    const char space[] = {' '};

    char moves[] = {'U', 'F', 'R'};
    char currMove[2] = {moves[getRandomNum(0, 2+1)], '\0'};
    char prevMove[2] = {'\0'};

    std::string alg;

    for (int i = 0; i < getRandomNum(9, 12); ++i) {
        alg += currMove;
        int extra = getRandomNum(1,3+1);

        if (extra == 1)
        {
            alg += '\'';
        } else if(extra == 2){
            alg += '2';
        }
        alg += space;

        prevMove[0] = currMove[0];
        while (currMove[0] == prevMove[0]) {
            currMove[0] = moves[getRandomNum(0, 2+1)];
        }
    }

    std::string result;

    // Remove non-printable characters and excessive spaces
    for (char c : alg) {
        if (isprint(c)) {
            result += c;
        } else if (c == ' ') {
            if (result.empty() || result.back() != ' ') {
                result += c;
            }
        }
    }

    return result;
}

std::string Three_By_Three() {
    const char space[] = {' '};

    char moves[] = {'U', 'F', 'R', 'B', 'L', 'D'};
    char currMove[2] = {moves[getRandomNum(0, 5+1)], '\0'};
    char prevMove[2] = {'\0'};

    std::string alg;

    for (int i = 0; i < getRandomNum(20, 25); ++i) {
        alg += currMove;
        int extra = getRandomNum(1,3+1);

        if (extra == 1)
        {
            alg += '\'';
        } else if(extra == 2){
            alg += '2';
        }
        alg += space;



        prevMove[0] = currMove[0];
        while (currMove[0] == prevMove[0]) {
            currMove[0] = moves[getRandomNum(0, 5+1)];
        }
    }

    std::string result;

    // Remove non-printable characters and excessive spaces
    for (char c : alg) {
        if (isprint(c)) {
            result += c;
        } else if (c == ' ') {
            if (result.empty() || result.back() != ' ') {
                result += c;
            }
        }
    }

    return result;
}

std::string Four_By_Four() {
    const char space[] = {' '};

    char moves[] = {'U', 'F', 'R', 'B', 'L', 'D'};
    char currMove[2] = {moves[getRandomNum(0, 5+1)], '\0'};
    char prevMove[2] = {'\0'};

    std::string alg;

    int wide;
    int extra;

    for (int i = 0; i < getRandomNum(35, 42); ++i) {
        alg += currMove;

        if (*currMove == 'U' || *currMove == 'F' || *currMove == 'R')
        {
        wide = getRandomNum(1,2+1);
        if (wide == 1)
        {
            alg += 'w';
        }}

        extra = getRandomNum(1,3+1);

        if (extra == 1)
        {
            alg += '\'';
        } else if(extra == 2){
            alg += '2';
        }
        alg += space;



        prevMove[0] = currMove[0];
        while (currMove[0] == prevMove[0]) {
            currMove[0] = moves[getRandomNum(0, 5+1)];
        }
    }

    std::string result;

    // Remove non-printable characters and excessive spaces
    for (char c : alg) {
        if (isprint(c)) {
            result += c;
        } else if (c == ' ') {
            if (result.empty() || result.back() != ' ') {
                result += c;
            }
        }
    }

    return result;
}

std::string Five_By_Five() {
    const char space[] = {' '};

    char moves[] = {'U', 'F', 'R', 'B', 'L', 'D'};
    char currMove[2] = {moves[getRandomNum(0, 5+1)], '\0'};
    char prevMove[2] = {'\0'};

    std::string alg;

    int wide;
    int extra;

    for (int i = 0; i < getRandomNum(48, 53); ++i) {
        alg += currMove;

        wide = getRandomNum(1,2+1);
        if (wide == 1)
        {
            alg += 'w';
        }

        extra = getRandomNum(1,3+1);

        if (extra == 1)
        {
            alg += '\'';
        } else if(extra == 2){
            alg += '2';
        }
        alg += space;



        prevMove[0] = currMove[0];
        while (currMove[0] == prevMove[0]) {
            currMove[0] = moves[getRandomNum(0, 5+1)];
        }
    }

    std::string result;

    // Remove non-printable characters and excessive spaces
    for (char c : alg) {
        if (isprint(c)) {
            result += c;
        } else if (c == ' ') {
            if (result.empty() || result.back() != ' ') {
                result += c;
            }
        }
    }

    return result;
}

std::string Six_By_Six() {
    const char space[] = {' '};

    char moves[] = {'U', 'F', 'R', 'B', 'L', 'D'};
    char currMove[2] = {moves[getRandomNum(0, 5+1)], '\0'};
    char prevMove[2] = {'\0'};

    std::string alg;

    int wide;
    int extra;

    for (int i = 0; i < getRandomNum(58,63); ++i) {
        alg += currMove;



        wide = getRandomNum(1,2+1);
        if (wide == 1)
        {
            if ((*currMove == 'U' || *currMove == 'F' || *currMove == 'R') && (getRandomNum(1,3) == 1))
            {
                alg += "3";
            }
            alg += 'w';
        }

        extra = getRandomNum(1,3+1);

        if (extra == 1)
        {
            alg += '\'';
        } else if(extra == 2){
            alg += '2';
        }
        alg += space;



        prevMove[0] = currMove[0];
        while (currMove[0] == prevMove[0]) {
            currMove[0] = moves[getRandomNum(0, 5+1)];
        }
    }

    std::string result;

    // Remove non-printable characters and excessive spaces
    for (char c : alg) {
        if (isprint(c)) {
            result += c;
        } else if (c == ' ') {
            if (result.empty() || result.back() != ' ') {
                result += c;
            }
        }
    }

    return result;
}

std::string Seven_By_Seven() {
    const char space[] = {' '};

    char moves[] = {'U', 'F', 'R', 'B', 'L', 'D'};
    char currMove[2] = {moves[getRandomNum(0, 5+1)], '\0'};
    char prevMove[2] = {'\0'};

    std::string alg;

    int wide;
    int extra;

    for (int i = 0; i < getRandomNum(68,73); ++i) {
        alg += currMove;



        wide = getRandomNum(1,2+1);
        if (wide == 1)
        {
            if (getRandomNum(1,3) == 1)
            {
                alg += "3";
            }
            alg += 'w';
        }

        extra = getRandomNum(1,3+1);

        if (extra == 1)
        {
            alg += '\'';
        } else if(extra == 2){
            alg += '2';
        }
        alg += space;



        prevMove[0] = currMove[0];
        while (currMove[0] == prevMove[0]) {
            currMove[0] = moves[getRandomNum(0, 5+1)];
        }
    }

    std::string result;

    // Remove non-printable characters and excessive spaces
    for (char c : alg) {
        if (isprint(c)) {
            result += c;
        } else if (c == ' ') {
            if (result.empty() || result.back() != ' ') {
                result += c;
            }
        }
    }

    return result;
}

std::string Skewb() {
    const char space[] = {' '};

    char moves[] = {'U', 'L', 'R', 'B'};
    char currMove[2] = {moves[getRandomNum(0, 3+1)], '\0'};
    char prevMove[2] = {'\0'};

    std::string alg;

    for (int i = 0; i < getRandomNum(9, 12); ++i) {
        alg += currMove;
        int extra = getRandomNum(1,2+1);

        if (extra == 1)
        {
            alg += '\'';
        }
        alg += space;

        prevMove[0] = currMove[0];
        while (currMove[0] == prevMove[0]) {
            currMove[0] = moves[getRandomNum(0, 2+1)];
        }
    }

    std::string result;

    // Remove non-printable characters and excessive spaces
    for (char c : alg) {
        if (isprint(c)) {
            result += c;
        } else if (c == ' ') {
            if (result.empty() || result.back() != ' ') {
                result += c;
            }
        }
    }

    return result;
}

std::string Megaminx(){
    const char space[] = {' '};
    char prevMove[2] = {'\0'};
    bool Dpp;

    std::string alg;

    for (int n = 0; n < 5; ++n)
    {    
        for (int i = 0; i < 7; ++i)
        {
            alg += 'R';
            if (getRandomNum(1,2+1) == 1)
            {
                    alg += '+'; alg += '+'; //Bruh
                    alg += space;
                }else{
                    alg += '-'; alg += '-';
                    alg += space;
            }

            alg += 'D';
            if (getRandomNum(1,2+1) == 1)
            {
                    alg += '+'; alg += '+';
                    Dpp = true;
                    alg += space;
                }else{
                    alg += '-'; alg += '-';
                    Dpp = false;
                    alg += space;
            }
        }
        if(Dpp){
            alg += 'U';
        }else{
            alg += 'U';
            alg += '\''; 
        }
        alg += '\n';
    }

     std::string result;

    // Remove non-printable characters and excessive spaces
    for (char c : alg) {
        if (isprint(c)) {
            result += c;
        } else if (c == ' ') {
            if (result.empty() || result.back() != ' ') {
                result += c;
            }
        }
    }

    
    return alg;  
}

std::string Pyraminx() {
    const char space[] = {' '};

    char moves[] = {'U', 'L', 'R', 'B'};
    char tips[] = {'u', 'l', 'r', 'b'};
    char currMove[2] = {moves[getRandomNum(0, 3+1)], '\0'};
    char prevMove[2] = {'\0'};

    std::string alg;

    for (int i = 0; i < getRandomNum(9, 12); ++i) {
        alg += currMove;
        int extra = getRandomNum(1,2+1);

        if (extra == 1)
        {
            alg += '\'';
        }
        alg += space;

        prevMove[0] = currMove[0];
        while (currMove[0] == prevMove[0]) {
            currMove[0] = moves[getRandomNum(0, 2+1)];
        }
    }

    char TcurrMove[2] = {tips[getRandomNum(0, 3+1)], '\0'};
    char TprevMove[2] = {'\0'};

    // Tips
    for (int i = 0; i < getRandomNum(1, 4); ++i) {
        alg += TcurrMove;
        int extra = getRandomNum(1,2+1);

        if (extra == 1)
        {
            alg += '\'';
        }
        alg += space;

        TprevMove[0] = TcurrMove[0];
        while (TcurrMove[0] == TprevMove[0]) {
            TcurrMove[0] = tips[getRandomNum(0, 3+1)];
        }
    }

    std::string result;

    // Remove non-printable characters and excessive spaces
    for (char c : alg) {
        if (isprint(c)) {
            result += c;
        } else if (c == ' ') {
            if (result.empty() || result.back() != ' ') {
                result += c;
            }
        }
    }

    return result;
}
