#pragma once
#include "self_random.hpp"

self_random rng; 

#include "NxN_move_gen.hpp"
#include "square_one.hpp"

// Oh yeah!! Weird header stuff my beloved!!!

static bool canUseMove(const puzzle_move *pMove1, const puzzle_move *pMove2)
{ // Two x Two
    return pMove1->base != pMove2->base;
}

static bool canUseMove(const puzzle_move *pMove1, const puzzle_move *pMove2, const puzzle_move *pMove3)
{
    if (!canUseMove(pMove2, pMove3))
    {
        return false;
    }
    if (!(pMove3->wsize != pMove2->wsize && pMove3->wsize != pMove1->wsize))
    {
        switch (pMove3->base)
        {
        case baseMoves::U:
            return !(pMove1->base == baseMoves::U && pMove2->base == baseMoves::D);

        case baseMoves::F:
            return !(pMove1->base == baseMoves::F && pMove2->base == baseMoves::B);

        case baseMoves::R:
            return !(pMove1->base == baseMoves::R && pMove2->base == baseMoves::L);

        case baseMoves::D:
            return !(pMove2->base == baseMoves::U && pMove1->base == baseMoves::D);

        case baseMoves::B:
            return !(pMove2->base == baseMoves::F && pMove1->base == baseMoves::B);

        case baseMoves::L:
            return !(pMove2->base == baseMoves::R && pMove1->base == baseMoves::L);

        default:
            return true;
        }
    }

    return true;
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

std::string moveVectorToString(const std::vector<puzzle_move> &moves)
{
    std::string scramble;
    for (const puzzle_move &move : moves)
    {
        scramble += getRepresentation(&move) + ' ';
    }
    return scramble;
}

static std::string Two_By_Two()
{
    std::vector<puzzle_move> scramble;
    puzzle_move Move{};
    puzzle_move PrevMove{};
    const int moveCount = getRandomNum(9, 13);

    // So PrevMove is initalised.
    createMove(PrevMove, '2');

    scramble.push_back(PrevMove);

    for (int n = 0; n < moveCount; n++)
    {
        do
        {
            createMove(Move, '2');
        } while (!canUseMove(&PrevMove, &Move));

        scramble.push_back(Move);
        PrevMove = Move; // Don't forget this!! :DDDDDDDDDD
    }
    return moveVectorToString(scramble);
}

static std::string Three_By_Three(const bool blind)
{
    std::vector<puzzle_move> scramble;
    puzzle_move Move{};
    puzzle_move PrevMove{};
    puzzle_move TwoPrevMove{};
    const int moveCount = getRandomNum(19, 27);

    // So TwoPrevMove is initialised
    createMove(TwoPrevMove, '3');

    // So PrevMove is initalised.
    do
    {
        createMove(PrevMove, '3');
    } while (!canUseMove(&TwoPrevMove, &PrevMove));

    int cubeWideCount = getRandomNum(1, 2);
    for (int n = 0 + cubeWideCount * blind; n < moveCount; n++)
    {
        do
        {
            createMove(Move, '3');
        } while (!canUseMove(&TwoPrevMove, &PrevMove, &Move));

        scramble.push_back(Move);

        TwoPrevMove = PrevMove;
        PrevMove = Move;
    }

    if (blind)
    {
        for (int i = 0; i < cubeWideCount; i++)
        {
            do
            {
                createMove(Move, '2'); // 2x2 for U, F and R moves.
            } while (!canUseMove(&TwoPrevMove, &PrevMove, &Move));

            Move.wsize = wideSizes::WIDE;

            scramble.push_back(Move);

            TwoPrevMove = PrevMove;
            PrevMove = Move;
        }
    }
    return moveVectorToString(scramble);
}

static std::string MBLD(struct BLD blind)
{
    std::stringstream out;
    for (int c = 1; c < blind.count + 1; c++)
    {
        out << c << ": " << Three_By_Three(blind.on) << "\n";
    }
    return out.str();
}

static std::string FMC()
{
    // R' U' F ... R' U' F

    std::vector<puzzle_move> scramble;

    const puzzle_move R_Prime{baseMoves::R, directions::ACW, wideSizes::NONE};
    const puzzle_move U_Prime{baseMoves::U, directions::ACW, wideSizes::NONE};
    const puzzle_move F{baseMoves::F, directions::CW, wideSizes::NONE};

    scramble.push_back(R_Prime);
    scramble.push_back(U_Prime);
    scramble.push_back(F);

    puzzle_move Move = F;
    puzzle_move PrevMove = U_Prime;
    puzzle_move TwoPrevMove = R_Prime;
    const int moveCount = getRandomNum(19, 27) - 6;

    TwoPrevMove = PrevMove;
    PrevMove = Move;

    for (int i = 0; i < moveCount - 1; i++)
    {
        do
        {
            createMove(Move, '3');
        } while (!canUseMove(&TwoPrevMove, &PrevMove, &Move));

        scramble.push_back(Move);
        TwoPrevMove = PrevMove;
        PrevMove = Move;
    }

    // Generate last 3 moves. Make sure that the first R' is compatible with the last 2 moves.

    do
    {
        createMove(Move, '3');
    } while (!canUseMove(&PrevMove, &Move, &R_Prime));

    scramble.push_back(Move);
    scramble.push_back(R_Prime);
    scramble.push_back(U_Prime);
    scramble.push_back(F);

    return moveVectorToString(scramble);
}

static std::string Four_By_Four(bool blind)
{
    std::vector<puzzle_move> scramble;
    puzzle_move Move{};
    puzzle_move PrevMove{};
    puzzle_move TwoPrevMove{};
    const int moveCount = getRandomNum(38, 43);
    int wideMoveCount = getRandomNum(12, 16); // n*3 to n*4

    // So TwoPrevMove is initialised
    createMove(TwoPrevMove, '4');

    // So PrevMove is initalised.
    do
    {
        createMove(PrevMove, '4');
    } while (!canUseMove(&TwoPrevMove, &PrevMove));

    int cubeRotateCount = getRandomNum(1, 2);
    for (int n = 0 + cubeRotateCount * blind; n < moveCount; n++)
    {

        do
        {
            createMove(Move, '4');
        } while (!canUseMove(&TwoPrevMove, &PrevMove, &Move));

        scramble.push_back(Move);

        if (Move.wsize != wideSizes::NONE)
        {
            wideMoveCount--;
        }

        TwoPrevMove = PrevMove;
        PrevMove = Move; //
    }

    int moveIndex;

    while (wideMoveCount > 0)
    {
        do
        {
            moveIndex = getRandomNum(0, scramble.size() - 1);

            scramble.at(moveIndex).wsize = wideSizes::WIDE;

        } while (scramble.at(moveIndex).wsize == wideSizes::NONE &&
                 (scramble.at(moveIndex).base == baseMoves::U ||
                  scramble.at(moveIndex).base == baseMoves::F ||
                  scramble.at(moveIndex).base == baseMoves::R));

        wideMoveCount--;
    }

    std::string outputScramble = moveVectorToString(scramble);

    if (blind)
    {
        for (int k = 0; k < cubeRotateCount; k++)
        {
            outputScramble += (char)('x' + k);
            int dir = getRandomNum(1, 3);
            if (dir == 2)
            {
                outputScramble += '2';
            }
            else if (dir == 3)
            {
                outputScramble += '\'';
            }
            outputScramble += ' ';
        }
    }
    return outputScramble;
}

static std::string Five_By_Five(bool blind)
{
    std::vector<puzzle_move> scramble;
    puzzle_move Move{};
    puzzle_move PrevMove{};
    puzzle_move TwoPrevMove{};
    const int moveCount = getRandomNum(48, 53);
    int wideMoveCount = getRandomNum(15, 20);

    // So TwoPrevMove is initialised
    createMove(TwoPrevMove, '5');

    // So PrevMove is initalised.
    do
    {
        createMove(PrevMove, '5');
    } while (!canUseMove(&TwoPrevMove, &PrevMove));

    int cubeWideCount = getRandomNum(1, 2);
    for (int n = 0 + cubeWideCount * blind; n < moveCount; n++)
    {
        do
        {
            createMove(Move, '5');
        } while (!canUseMove(&TwoPrevMove, &PrevMove, &Move));

        scramble.push_back(Move);

        if (Move.wsize != wideSizes::NONE)
        {
            wideMoveCount--;
        }

        TwoPrevMove = PrevMove;
        PrevMove = Move; //
    }

    // Randomly add wide moves
    int moveIndex = getRandomNum(0, scramble.size() - 1);

    while (wideMoveCount > 0)
    {
        do
        {
            scramble.at(moveIndex).wsize = wideSizes::WIDE;
        } while (scramble.at(moveIndex).wsize == wideSizes::NONE);

        wideMoveCount--;
    }

    if (blind)
    {
        for (int i = 0; i < cubeWideCount; i++)
        {
            do
            {
                createMove(Move, '2'); // 2x2 for U, F and R moves.
            } while (!canUseMove(&TwoPrevMove, &PrevMove, &Move));

            Move.wsize = wideSizes::WIDE2;
            scramble.push_back(Move);

            TwoPrevMove = PrevMove;
            PrevMove = Move;
        }
    }
    return moveVectorToString(scramble);
}

static std::string Six_By_Six()
{
    std::vector<puzzle_move> scramble;
    puzzle_move Move{};
    puzzle_move PrevMove{};
    puzzle_move TwoPrevMove{};
    const int moveCount = getRandomNum(58, 63);
    int wideMoveCount = getRandomNum(18, 24);

    // So TwoPrevMove is initialised
    createMove(TwoPrevMove, '6');

    // So PrevMove is initalised.
    do
    {
        createMove(PrevMove, '6');
    } while (!canUseMove(&TwoPrevMove, &PrevMove));

    for (int n = 0; n < moveCount; n++)
    {

        do
        {
            createMove(Move, '6');
        } while (!canUseMove(&TwoPrevMove, &PrevMove, &Move));

        scramble.push_back(Move);

        if (Move.wsize != wideSizes::NONE)
        {
            wideMoveCount--;
        }

        TwoPrevMove = PrevMove;
        PrevMove = Move; //
    }

    // Randomly add wide moves
    int moveIndex = getRandomNum(0, scramble.size() - 1);

    while (wideMoveCount > 0)
    {
        do
        {
            scramble.at(moveIndex).wsize = wideSizes::WIDE;
        } while (scramble.at(moveIndex).wsize == wideSizes::NONE);

        wideMoveCount--;
    }

    return moveVectorToString(scramble);
}

static std::string Seven_By_Seven()
{
    std::vector<puzzle_move> scramble;
    puzzle_move Move{};
    puzzle_move PrevMove{};
    puzzle_move TwoPrevMove{};
    const int moveCount = getRandomNum(68, 73);
    int wideMoveCount = getRandomNum(21, 28);

    // So TwoPrevMove is initialised
    createMove(TwoPrevMove, '7');

    // So PrevMove is initalised.
    do
    {
        createMove(PrevMove, '7');
    } while (!canUseMove(&TwoPrevMove, &PrevMove));

    for (int n = 0; n < moveCount; n++)
    {

        do
        {
            createMove(Move, '7');
        } while (!canUseMove(&TwoPrevMove, &PrevMove, &Move));

        scramble.push_back(Move);

        if (Move.wsize != wideSizes::NONE)
        {
            wideMoveCount--;
        }

        TwoPrevMove = PrevMove;
        PrevMove = Move;
    }

    // Randomly add wide moves
    int moveIndex = getRandomNum(0, scramble.size() - 1);

    while (wideMoveCount > 0)
    {
        do
        {
            scramble.at(moveIndex).wsize = wideSizes::WIDE;
        } while (scramble.at(moveIndex).wsize == wideSizes::NONE);

        wideMoveCount--;
    }

    return moveVectorToString(scramble);
}

static std::string Skewb()
{
    std::vector<puzzle_move> scramble;
    puzzle_move Move{};
    puzzle_move PrevMove{};
    const int moveCount = getRandomNum(9, 13);

    // So PrevMove is initalised.
    createMove(PrevMove, 'S');

    for (int n = 0; n < moveCount; n++)
    {
        do
        {
            createMove(Move, 'S');
        } while (!canUseMove(&PrevMove, &Move));

        scramble.push_back(Move);
        PrevMove = Move; // Don't forget this!! :DDDDDDDDDD
    }
    return moveVectorToString(scramble);
}

static std::string Megaminx()
{
    bool Dpp;
    std::ostringstream scramble;

    for (int i = 0; i < 5; i++)
    {
        for (int n = 0; n < 7; n++)
        {
            scramble << "R";
            if (getRandomNum(0, 1) == 0)
            {
                scramble << "++ ";
            }
            else
            {
                scramble << "-- ";
            }

            scramble << "D";
            if (getRandomNum(0, 1) == 0)
            {
                scramble << "++ ";
                Dpp = true;
            }
            else
            {
                scramble << "-- ";
                Dpp = false;
            }
        }
        if (Dpp)
        {
            scramble << "U \n";
        }
        else
        {
            scramble << "U' \n";
        }
    }
    return scramble.str();
}

static std::string Pyraminx()
{
    constexpr char tips[] = {'u', 'l', 'r', 'b'};
    std::ostringstream scramble;
    scramble << Skewb();

    for (int i = 0; i < 3; i++)
    {
        if (const int direction = getRandomNum(1, 3); direction == 1)
        {
            continue;
        }
        else if (direction == 2)
        {
            scramble << tips[i];
            scramble << " ";
        }
        else if (direction == 3)
        {
            scramble << tips[i];
            scramble << "' ";
        }
    }
    return scramble.str();
}

static std::string Clock()
{
    const std::string hours[] = {"5-", "4-", "3-", "2-", "1-", "0+", "1+", "2+", "3+", "4+", "5+", "6+"};
    std::ostringstream scramble;
    scramble << "UR" << hours[getRandomNum(0, 11)] << " "
             << "DR" << hours[getRandomNum(0, 11)] << " "
             << "DL" << hours[getRandomNum(0, 11)] << " "
             << "UL" << hours[getRandomNum(0, 11)] << " "
             << "U" << hours[getRandomNum(0, 11)] << " "
             << "R" << hours[getRandomNum(0, 11)] << " "
             << "D" << hours[getRandomNum(0, 11)] << " "
             << "L" << hours[getRandomNum(0, 11)] << " "
             << "ALL" << hours[getRandomNum(0, 11)] << " " << "y2" << " "
             << "U" << hours[getRandomNum(0, 11)] << " "
             << "R" << hours[getRandomNum(0, 11)] << " "
             << "D" << hours[getRandomNum(0, 11)] << " "
             << "L" << hours[getRandomNum(0, 11)] << " "
             << "ALL" << hours[getRandomNum(0, 11)];

    return scramble.str();
}

// Use this one
inline std::string generate_scramble(const char cube, const struct BLD blind, const bool fmc)
{
    switch (cube)
    {
    case '2':
        return Two_By_Two();

    case '3':
        if (fmc)
        {
            return FMC();
        }
        else
        {
            if (blind.count <= 1)
            {
                return Three_By_Three(blind.on);
            }
            else
            {
                return MBLD(blind);
            }
        }

    case '4':
        return Four_By_Four(blind.on);

    case '5':
        return Five_By_Five(blind.on);

    case '6':
        return Six_By_Six();

    case '7':
        return Seven_By_Seven();

    case 'S':
        return Skewb();

    case 'P':
        return Pyraminx();

    case 'M':
        return Megaminx();

    case 'C':
        return Clock();

    case 'Q':
        return sq1::generateScramble();

    default:
        return "Unknown puzzle";
    }
}
