#pragma once


#include <iostream>
#include <vector>
#include <pthread.h>
#include <atomic>

#include <cmath>
#include <ctime>

#define _USE_MATH_DEFINES

typedef struct args{
    double radius = 0;
    size_t dotsPerThread = 0;
    unsigned * seed = nullptr;
} Args;

typedef struct{
    double x = 0;
    double y = 0;
}Coordinats;

bool IsInCircle(const Coordinats &cords, const double radius);

Coordinats CreateRandCoord(const double radius, unsigned int * seed);

void *task(void *input);

double CircleArea(const size_t threadQuantity, const double radius, const size_t dotsQuantity);