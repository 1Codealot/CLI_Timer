#include "NxNMoveGen.hpp"

bool canUseMove(struct move *pMove1, struct move *pMove2){ // Two x Two
    return pMove1->base != pMove2->base;
}

bool canUseMove(struct move *pMove1, struct move *pMove2, struct move *pMove3){
    if (!canUseMove(pMove2, pMove3)){
        return false;
    }
    if(!(pMove3->wsize != pMove2->wsize && pMove3->wsize != pMove1->wsize)){
        switch (pMove3->base)
        {
        case 'U':
            return !(pMove1->base == 'U' && pMove2->base == 'D');
        
        case 'F':
            return !(pMove1->base == 'F' && pMove2->base == 'B');

        case 'R':
            return !(pMove1->base == 'R' && pMove2->base == 'L');

        case 'D':
            return !(pMove2->base == 'U' && pMove1->base == 'D');
        
        case 'B':
            return !(pMove2->base == 'F' && pMove1->base == 'B');

        case 'L':
            return !(pMove2->base == 'R' && pMove1->base == 'L');

        default:
            return true;
        }
    }
    else {
        return true;
    }
}


/*
######################################################NOTE################################################################
How to use above functions:
```
do{
    createMove(//whatever);
}while(!canUseMove(&TwoPrevMove, &PrevMove, &Move));
```
You need a minimum of 2 references to a move struct.
*/


std::string Two_By_Two(){
    std::string scramble;
    struct move Move;
    struct move PrevMove;
    int moveCount = getRandomNum(9, 13);
    
    // So PrevMove is initalised.
    createMove(PrevMove, '2');

    for (int n = 0; n < moveCount; n++)
    {
        do
        {
            createMove(Move, '2');
        } while (!canUseMove(&PrevMove, &Move));
        

        scramble += getRepresentation(&Move) + ' ';
        PrevMove = Move; // Don't forget this!! :DDDDDDDDDD
    }
    return scramble;
}

std::string Three_By_Three(){
    std::string scramble;
    struct move Move;
    struct move PrevMove;
    struct move TwoPrevMove;
    int moveCount = getRandomNum(19, 27);
    
    // So TwoPrevMove is initialised
    createMove(TwoPrevMove, '3');

    // So PrevMove is initalised.
   do{
    createMove(PrevMove, '3');
    }while(!canUseMove(&TwoPrevMove, &PrevMove));

    for (int n = 0; n < moveCount; n++)
    {

        do
        {
            createMove(Move, '3');
        } while (!canUseMove(&TwoPrevMove, &PrevMove, &Move));
        

        scramble += getRepresentation(&Move) + ' ';
        TwoPrevMove = PrevMove;
        PrevMove = Move; // 
    }
    return scramble;
}

std::string Four_By_Four(){
    std::string scramble;
    struct move Move;
    struct move PrevMove;
    struct move TwoPrevMove;
    int moveCount = getRandomNum(38, 43);
    
    // So TwoPrevMove is initialised
    createMove(TwoPrevMove, '4');

    // So PrevMove is initalised.
   do{
    createMove(PrevMove, '4');
    }while(!canUseMove(&TwoPrevMove, &PrevMove));

    for (int n = 0; n < moveCount; n++)
    {

        do
        {
            createMove(Move, '4');
        } while (!canUseMove(&TwoPrevMove, &PrevMove, &Move));
        

        scramble += getRepresentation(&Move) + " ";
        TwoPrevMove = PrevMove;
        PrevMove = Move; // 
    }
    return scramble;
}

std::string Five_By_Five(){
    std::string scramble;
    struct move Move;
    struct move PrevMove;
    struct move TwoPrevMove;
    int moveCount = getRandomNum(48, 53);
    
    // So TwoPrevMove is initialised
    createMove(TwoPrevMove, '5');

    // So PrevMove is initalised.
   do{
    createMove(PrevMove, '5');
    }while(!canUseMove(&TwoPrevMove, &PrevMove));

    for (int n = 0; n < moveCount; n++)
    {

        do
        {
            createMove(Move, '5');
        } while (!canUseMove(&TwoPrevMove, &PrevMove, &Move));
        

        scramble += getRepresentation(&Move) + " ";
        TwoPrevMove = PrevMove;
        PrevMove = Move; // 
    }
    return scramble;
}

std::string Six_By_Six(){
    std::string scramble;
    struct move Move;
    struct move PrevMove;
    struct move TwoPrevMove;
    int moveCount = getRandomNum(58, 63);
    
    // So TwoPrevMove is initialised
    createMove(TwoPrevMove, '6');

    // So PrevMove is initalised.
   do{
    createMove(PrevMove, '6');
    }while(!canUseMove(&TwoPrevMove, &PrevMove));

    for (int n = 0; n < moveCount; n++)
    {

        do
        {
            createMove(Move, '6');
        } while (!canUseMove(&TwoPrevMove, &PrevMove, &Move));
        

        scramble += getRepresentation(&Move) + " ";
        TwoPrevMove = PrevMove;
        PrevMove = Move; // 
    }
    return scramble;
}

std::string Seven_By_Seven(){
    std::string scramble;
    struct move Move;
    struct move PrevMove;
    struct move TwoPrevMove;
    int moveCount = getRandomNum(68, 73);
    
    // So TwoPrevMove is initialised
    createMove(TwoPrevMove, '7');

    // So PrevMove is initalised.
   do{
    createMove(PrevMove, '7');
    }while(!canUseMove(&TwoPrevMove, &PrevMove));

    for (int n = 0; n < moveCount; n++)
    {

        do
        {
            createMove(Move, '7');
        } while (!canUseMove(&TwoPrevMove, &PrevMove, &Move));
        

        scramble += getRepresentation(&Move) + " ";
        TwoPrevMove = PrevMove;
        PrevMove = Move; // 
    }
    return scramble;
}

std::string Skewb(){
    std::string scramble;
    struct move Move;
    struct move PrevMove;
    int moveCount = getRandomNum(9, 13);
    
    // So PrevMove is initalised.
    createMove(PrevMove, 'S');

    for (int n = 0; n < moveCount; n++)
    {
        do
        {
            createMove(Move, 'S');
        } while (!canUseMove(&PrevMove, &Move));
        

        scramble += getRepresentation(&Move) + ' ';
        PrevMove = Move; // Don't forget this!! :DDDDDDDDDD
    }
    return scramble;
}

std::string Megaminx(){
    bool Dpp;
    std::string scramble;

    for (int i = 0; i < 5; i++)
    {
        for (int n = 0; n < 7; n++){
            scramble += "R";
            if(getRandomNum(0, 1) == 0){
                scramble += "++ ";
            } else {
                scramble += "-- ";
            }

            scramble += "D";
            if(getRandomNum(0, 1) == 0){
                scramble += "++ ";
                Dpp = true;
            } else {
                scramble += "-- ";
                Dpp = false;
            }
        }
        if (Dpp)
        {
            scramble += "U \n";
        } 
        else
        {
            scramble += "U' \n";
        }
    }
    return scramble;
}

std::string Pyraminx() {
    char tips[] = {'u', 'l', 'r', 'b'};
    std::string scramble = Skewb();

    for(int i = 0; i < 3; i++){
        int direction = getRandomNum(1, 3);
        if (direction == 1)
        {
            continue;
        }
        else if (direction == 2)
        {  
            scramble += tips[i];
            scramble += " ";
        }
        else if (direction == 3)
        {
            scramble += tips[i];
            scramble += "' ";
        }
    }
    return scramble;
}

std::string Clock(){
    std::string moves[] = {"5-","4-","3-","2-","1-","0+","1+","2+","3+","4+","5+","6+"};
    std::string scramble;

    scramble += 
    "UR" + moves[getRandomNum(0, 12)] + " " +
    "DR" + moves[getRandomNum(0, 12)] + " " +
    "DL" + moves[getRandomNum(0, 12)] + " " +
    "UL" + moves[getRandomNum(0, 12)] + " " +
    "U"   + moves[getRandomNum(0, 12)] + " " +
    "R"   + moves[getRandomNum(0, 12)] + " " +
    "D"   + moves[getRandomNum(0, 12)] + " " +
    "L"   + moves[getRandomNum(0, 12)] + " " +
    "ALL"+ moves[getRandomNum(0, 12)] + " " + "y2" + " " +
    "U"   + moves[getRandomNum(0, 12)] + " " +
    "R"   + moves[getRandomNum(0, 12)] + " " +
    "D"   + moves[getRandomNum(0, 12)] + " " +
    "L"   + moves[getRandomNum(0, 12)] + " ";

    if (getRandomNum(0, 1) == 1)
    {
        scramble += "UR ";
    }
    if (getRandomNum(0, 1) == 1)
    {
        scramble += "DR ";
    }
    if (getRandomNum(0, 1) == 1)
    {
        scramble += "DL ";
    }
    if (getRandomNum(0, 1) == 1)
    {
        scramble += "UL ";
    }
    
    return scramble;
}