#pragma once
#include <queue>
#include <string>
#include <thread>
#include <chrono>

#include "scrambles.hpp"

#define CACHE_SIZE 50

void update_cache(std::queue<std::string> *cache, char cube, bool blind, bool fmc)
{
    while (true)
    {
        if (cache->size() < CACHE_SIZE)
        {
            cache->push(generate_scramble(cube, blind, fmc));
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
}