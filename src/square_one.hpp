#pragma once
#include <vector>
#include <random>
#include <string>

namespace sq1
{
    // Code sourced from <https://github.com/thewca/tnoodle-lib/blob/master/scrambles/src/main/java/org/worldcubeassociation/tnoodle/puzzle/SquareOnePuzzle.java>
    // It is also under the GNU General Public License v3.0 <https://github.com/thewca/tnoodle-lib/blob/master/LICENSE>

    inline std::random_device rng;

    static int getRandomTurnCount()
    {
        // -5 to +6
        return rng() % (6 + 1 - -5) + -5;
    }

    static void doSlash(std::vector<int> &pieces)
    {
        for (int i = 0; i < 6; i++)
        {
            std::swap(pieces.at(6 + i), pieces.at(12 + i));
        }
    }

    static bool canSlash(const std::vector<int> &pieces)
    {
        if (pieces.at(0) == pieces.at(11))
        {
            return false;
        }
        if (pieces.at(6) == pieces.at(5))
        {
            return false;
        }
        if (pieces.at(12) == pieces.at(23))
        {
            return false;
        }
        if (pieces.at(18) == pieces.at(17))
        {
            return false;
        }
        return true;
    }

    static std::vector<int> doRotateTopAndBottom(std::vector<int> pieces, int top, int bottom)
    {
        top = (-top % 12 + 12) % 12;

        std::vector<int> newPieces = std::vector<int>(std::move(pieces));
        std::vector<int> t;

        for (size_t n = 0; n < 12; n++)
        {
            t.push_back(newPieces.at(n));
        }

        for (size_t i = 0; i < 12; i++)
        {
            newPieces.at(i) = t.at((top + i) % 12);
        }

        bottom = (-bottom % 12 + 12) % 12;

        for (size_t n = 12; n < 24; n++)
        {
            t.at(n - 12) = newPieces.at(n);
        }

        for (size_t i = 0; i < 12; i++)
        {
            newPieces.at(i + 12) = t.at((bottom + i) % 12);
        }

        return newPieces;
    }

    inline std::string generateScramble()
    {
        std::string scramble;
        std::vector<int> pieces{0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11, 11, 12, 13, 13, 14, 15, 15};

        for (size_t x = 0; x <= rng() % 6 + 11; x++)
        {

            int top = 0;
            int bottom = 0;
            do
            {
                top = getRandomTurnCount();
                bottom = getRandomTurnCount();

                if (top == 0 && bottom == 0)
                {
                    continue;
                }

            } while (!canSlash(doRotateTopAndBottom(pieces, top, bottom)));

            pieces = doRotateTopAndBottom(pieces, top, bottom);
            doSlash(pieces);

            scramble += "(" + std::to_string(top) + ", " + std::to_string(bottom) + ") / ";
        }
        if (rng() % 2 == 0)
        {
            scramble.pop_back();
            scramble.pop_back();
        }

        return scramble;
    }

} // namespace sq1