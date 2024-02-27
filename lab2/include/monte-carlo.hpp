#pragma once


#include <iostream>
#include <vector>
#include <pthread.h>
#include <atomic>

#include <cmath>
#include <ctime>

struct Args{
    double radius = 0;
    size_t dotsPerThread = 0;
    std::atomic<size_t> * dotsInCircle = nullptr;
    unsigned seed = time(nullptr);
};

struct Coordinates{
    double x = 0;
    double y = 0;
};

bool IsInCircle(const Coordinates &cords, double radius);

Coordinates CreateRandCoord(double radius, unsigned int &seed);

void *task(void *input);

double CircleArea(size_t threadQuantity, double radius, size_t dotsQuantity);