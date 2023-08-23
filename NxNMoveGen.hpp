/*
This code is here to deprecate the original Scrambles.hpp and stringCleanup.hpp
*/

#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

int getRandomNum(int min, int max){
    return (rand() % (max+1 - min)) + min;
}

constexpr char baseMoves[] = {'F', 'U', 'R', 'B', 'L', 'D'};
constexpr char directions  [] = {' ','\'', '2'}; // If ' ' Ignore, can't have ''
constexpr char wideSizes  [] = {' ', '2', '3'};

struct move
{
    char base; // U F R B L D 
    char direction; // ' 2
    char wsize; // 0 2 3
};

void createMove(struct move &newMove, char moveType){ // no idea why I need struct move... in the func args.
    // Create empty move outside this func then pass it in here
    newMove.base = baseMoves[getRandomNum(0,5)];
    newMove.direction = directions[getRandomNum(0,2)]; // For skewb I can regen it
    newMove.wsize=wideSizes[0]; // YAYYY :/
    switch(moveType)
    {
        case '2':
            newMove.base = baseMoves[getRandomNum(0,2)];
            newMove.wsize=wideSizes[0];
            break;
        
        case '3':            
            newMove.wsize=wideSizes[0];
            break;
        
        case '4':
            if (newMove.base == 'U' || newMove.base == 'F' || newMove.base == 'R')
            {
                newMove.wsize = wideSizes[getRandomNum(0,1)];
            }
            break;

        case '5':
            newMove.wsize=wideSizes[getRandomNum(0, 1)];
            break; // World record case.

        case '6':
            if (newMove.base == 'U' || newMove.base == 'F' || newMove.base == 'R'){
                newMove.wsize=wideSizes[getRandomNum(0, 2)];
            } 
            else if (newMove.base == 'B' || newMove.base == 'L' || newMove.base == 'D')
            {
                newMove.wsize=wideSizes[getRandomNum(0, 1)];
            }
            break;  

        case '7':
            newMove.wsize=wideSizes[getRandomNum(0, 2)];
            break; // New world record

        case 'S':
            newMove.base=baseMoves[getRandomNum(1, 4)];
            newMove.direction = directions[getRandomNum(0,1)];
            newMove.wsize=wideSizes[0];
    }
}

std::string getRepresentation(struct move *pMove){
    std::string finalMove;
    finalMove += pMove->base;
    
    switch (pMove->wsize)
    {
    case wideSizes[1]:
        finalMove += "w";
        break;
    
    case wideSizes[2]:
        finalMove = "3" + finalMove + "w";
        break;
    
    default:
        break;
    }

    if (pMove->direction != ' '){
        finalMove += pMove->direction;
    }
    
    return finalMove;
}

std::string outputMove(char moveType){
    struct move Move;
    createMove(Move, moveType);
    return getRepresentation(&Move);
}
