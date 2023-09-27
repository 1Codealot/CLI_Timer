#include <iostream>

struct should
{
    bool Save;
    bool Continue;
    bool Prompt;
};

void updateShouldSave(const char *argv[]/*, struct should &Should*/){
    std::cout<< *argv;
}
