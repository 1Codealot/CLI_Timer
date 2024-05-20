// This exists because c++ <random> is a pain.

#include <chrono>

class self_random
{
private:
    size_t state;
public:
    self_random();
    ~self_random();

    size_t operator()();
    void seed(size_t s) {this->state = s;}
};

self_random::self_random()
{
    this->state = std::chrono::system_clock::now().time_since_epoch().count();
}

self_random::~self_random()
{
}

size_t self_random::operator()(){
    // https://en.wikipedia.org/wiki/Xorshift#Example_implementation
    if (sizeof(size_t) == 32/8) // 32 bit
    {
        size_t x = this->state;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        this->state = x;
        return x;
    }
    else // 64 bit, no (official) support for not 64 or 32 bit but no one uses those 
    {
        size_t x = this->state;
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 5;
        this->state = x;
        return x;
    }
    
}