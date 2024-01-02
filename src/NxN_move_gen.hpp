/*
This code is here to deprecate the original Scrambles.hpp and stringCleanup.hpp
*/
#pragma once

#include <sstream>
#include <random>

inline std::random_device rng;

static int getRandomNum(const int min, const int max)
{
    return rng() % (max + 1 - min) + min;
}

constexpr char baseMoves[6] = {'F', 'U', 'R', 'B', 'L', 'D'};
constexpr char directions[3] = {' ', '\'', '2'}; // If ' ' Ignore, can't have ''
constexpr char wideSizes[3] = {' ', '2', '3'};

typedef struct
{
    char base;      // U F R B L D
    char direction; // ' 2
    char wsize;     // 0 2 3
} puzzle_move;

inline void createMove(puzzle_move &newMove, const char moveType)
{
    // Create empty move outside this func then pass it in here
    newMove.base = baseMoves[getRandomNum(0, 5)];
    newMove.direction = directions[getRandomNum(0, 2)]; // For skewb I can regen it
    newMove.wsize = wideSizes[0];                       // YAYYY :/
    switch (moveType)
    {
    case '2':
        newMove.base = baseMoves[getRandomNum(0, 2)];
        newMove.wsize = wideSizes[0];
        break;

    case '3':
        newMove.wsize = wideSizes[0];
        break;

    case '4':
        if (newMove.base == 'U' || newMove.base == 'F' || newMove.base == 'R')
        {
            newMove.wsize = wideSizes[getRandomNum(0, 1)];
        }
        break;

    case '5':
        newMove.wsize = wideSizes[getRandomNum(0, 1)];
        break; // World record case.

    case '6':
        if (newMove.base == 'U' || newMove.base == 'F' || newMove.base == 'R')
        {
            newMove.wsize = wideSizes[getRandomNum(0, 2)];
        }
        else if (newMove.base == 'B' || newMove.base == 'L' || newMove.base == 'D')
        {
            newMove.wsize = wideSizes[getRandomNum(0, 1)];
        }
        break;

    case '7':
        newMove.wsize = wideSizes[getRandomNum(0, 2)];
        break; // New world record

    case 'S':
        newMove.base = baseMoves[getRandomNum(1, 4)];
        newMove.direction = directions[getRandomNum(0, 1)];
        newMove.wsize = wideSizes[0];
        break;

    default:
        newMove.base = 'B';
        newMove.direction = 'A';
        newMove.wsize = 'D';
        // Done as i cba to create a custom exception
    }
}

static inline std::string getRepresentation(const puzzle_move *pMove)
{
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

    if (pMove->direction != ' ')
    {
        finalMove += pMove->direction;
    }

    return finalMove;
}

std::ostringstream& operator<< (std::ostringstream& oss, const puzzle_move& pMove){
    oss << getRepresentation(&pMove);
    return oss;
}
