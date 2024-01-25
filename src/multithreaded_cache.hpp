#pragma once
#include <queue>
#include <string>
#include <future>
#include <chrono>

#include "scrambles.hpp"
#include "command_line_parser.hpp"

#define CACHE_SIZE 50

void update_cache(std::queue<std::string> *cache, struct should *Args)
{
    while (true)
    {
        if (cache->size() < CACHE_SIZE)
        {
            cache->push(generate_scramble(Args->cubeType, Args->blindfolded, Args->fmc));
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
}