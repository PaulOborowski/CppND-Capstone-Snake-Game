#ifndef GLOBALS_H
#define GLOBALS_H

#include <random>

// make random number generator global
extern std::random_device dev;
extern std::mt19937 engine;
extern std::uniform_int_distribution<int> random_w;
extern std::uniform_int_distribution<int> random_h;

#endif