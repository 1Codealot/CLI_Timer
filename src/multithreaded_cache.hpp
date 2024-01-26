#pragma once
#include <queue>
#include <string>
#include <chrono>

#include "scrambles.hpp"
#include "command_line_parser.hpp"

void update_cache(std::queue<std::string> *cache, const struct should *Args)
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