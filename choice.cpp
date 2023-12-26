#include <choice.h>
#include <random>
#include <limits>

int getRandomNumber(int range_low, int range_high) {
    static mt19937 engine{random_device{}()};
    uniform_int_distribution<int> dist(range_low, range_high);
    return dist(engine);
}