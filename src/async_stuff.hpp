#pragma once
#include <queue>
#include <string>
#include <chrono>

#include "scrambles.hpp"
#include "command_line_parser.hpp"

void update_cache(std::queue<std::string> *cache, const should *Args)
{
    while (Args->shouldContinue && Args->scrambleCount != 0)
    {
        if (cache->size() < Args->cache_size)
        {
            cache->push(generate_scramble(Args->cubeType, Args->blindfolded, Args->fmc));
            std::this_thread::sleep_for(std::chrono::milliseconds(200*(Args->needEnter)));
        }
    }
}

static int lastTerminalWidth = get_terminal_width();

void update_terminal(std::string *currentScramble, std::vector<float> *timesVector, const should *Args){
    while (Args->shouldContinue && Args->scrambleCount != 0){
        if (lastTerminalWidth != get_terminal_width()){
            lastTerminalWidth = get_terminal_width();
            clearScreen();

            output(*currentScramble, *timesVector, Args->shouldShowAvg);
        }
    }
}
