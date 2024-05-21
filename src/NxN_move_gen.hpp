/*
This code is here to deprecate the original Scrambles.hpp and stringCleanup.hpp
*/
#pragma once

#include <sstream>

static size_t getRandomNum(const int min, const int max)
{
    return rng() % (max + 1 - min) + min;
}

enum class baseMoves
{
    F,
    U,
    R,
    B,
    L,
    D
};

enum class directions
{
    CW,
    ACW,
    DOUBLE
};

enum class wideSizes
{
    NONE,
    WIDE,
    WIDE2
};

// SMH i wish i could overload `[]` for enums

constexpr baseMoves getElemFromEnumOfBaseMoves(size_t index)
{
    switch (index)
    {
    case 0:
        return baseMoves::F;
    case 1:
        return baseMoves::U;
    case 2:
        return baseMoves::R;
    case 3:
        return baseMoves::B;
    case 4:
        return baseMoves::L;
    case 5:
        return baseMoves::D;
    default:
        throw std::invalid_argument("Invalid index");
    }
}

constexpr directions getElemFromEnumOfDirections(size_t index)
{
    switch (index)
    {
    case 0:
        return directions::CW;
    case 1:
        return directions::ACW;
    case 2:
        return directions::DOUBLE;
    default:
        throw std::invalid_argument("Invalid index");
    }
}

constexpr wideSizes getElemFromEnumOfWidthSizes(size_t index)
{
    switch (index)
    {
    case 0:
        return wideSizes::NONE;
    case 1:
        return wideSizes::WIDE;
    case 2:
        return wideSizes::WIDE2;
    default:
        throw std::invalid_argument("Invalid index");
    }
}

typedef struct
{
    baseMoves base;
    directions direction;
    wideSizes wsize;
} puzzle_move;

inline void createMove(puzzle_move &newMove, const char moveType)
{
    // Create empty move outside this func then pass it in here
    newMove.base = getElemFromEnumOfBaseMoves(getRandomNum(0, 5));
    newMove.direction = getElemFromEnumOfDirections(getRandomNum(0, 2));
    newMove.wsize = getElemFromEnumOfWidthSizes(0); // YAYYY :/
    switch (moveType)
    {
    case '2':
        newMove.base = getElemFromEnumOfBaseMoves(getRandomNum(0, 2));
        break;

    case '3':
        break;

    case '4':
        if (newMove.base == baseMoves::U || newMove.base == baseMoves::F || newMove.base == baseMoves::R)
        {
            newMove.wsize = getElemFromEnumOfWidthSizes(getRandomNum(0, 1));
        }
        break;

    case '5':
        newMove.wsize = getElemFromEnumOfWidthSizes(getRandomNum(0, 1));
        break; // World record case.

    case '6':
        if (newMove.base == baseMoves::U || newMove.base == baseMoves::F || newMove.base == baseMoves::R)
        {
            newMove.wsize = getElemFromEnumOfWidthSizes(getRandomNum(0, 2));
        }
        else
        {
            newMove.wsize = getElemFromEnumOfWidthSizes(getRandomNum(0, 1));
        }
        break;

    case '7':
        newMove.wsize = getElemFromEnumOfWidthSizes(getRandomNum(0, 2));
        break; // New world record

    case 'S':
        newMove.base = getElemFromEnumOfBaseMoves(getRandomNum(1, 4));
        newMove.direction = getElemFromEnumOfDirections(getRandomNum(0, 1));
        break;

    default:
        throw std::invalid_argument("Invalid cube type");
    }
}

static inline std::string getRepresentation(const puzzle_move *pMove)
{
    std::string finalMove;
    switch (pMove->base)
    {
    case baseMoves::F:
        finalMove = "F";
        break;
    case baseMoves::U:
        finalMove = "U";
        break;
    case baseMoves::R:
        finalMove = "R";
        break;
    case baseMoves::B:
        finalMove = "B";
        break;
    case baseMoves::L:
        finalMove = "L";
        break;
    case baseMoves::D:
        finalMove = "D";
        break;
    default:
        throw std::invalid_argument("Invalid base move");
    }

    switch (pMove->wsize)
    {
    case wideSizes::WIDE:
        finalMove += "w";
        break;

    case wideSizes::WIDE2:
        finalMove = "3" + finalMove + "w";
        break;

    default:
        break;
    }

    switch (pMove->direction)
    {
    case directions::ACW:
        finalMove += "'";
        break;

    case directions::DOUBLE:
        finalMove += "2";
        break;

    default:
        break;
    }

    return finalMove;
}

std::ostringstream &operator<<(std::ostringstream &oss, const puzzle_move &pMove)
{
    oss << getRepresentation(&pMove);
    return oss;
}
