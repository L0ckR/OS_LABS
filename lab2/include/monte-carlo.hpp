#pragma once


#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

#include <cmath>
#include <ctime>

#define _USE_MATH_DEFINES

typedef struct{
    double x = 0;
    double y = 0;
}Coordinats;

bool IsInCircle(const Coordinats &cords, const double radius);

Coordinats CreateRandCoord(const double radius, unsigned int * seed);

void task(const double radius, std::atomic<size_t> &dotsInCircle, const size_t dotsPerThread, unsigned int * seed);

double CircleArea(const size_t threadQuantity, const double radius, const size_t dotsQuantity);