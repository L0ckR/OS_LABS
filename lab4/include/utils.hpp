#pragma once

#include <iostream>
#include <cstdlib>
#include <dlfcn.h>

using SinIntegralFunc = float (*)(float, float, float);
using SortFunc = int* (*)(int* , size_t);

void* LoadLibrary(const char *libraryName);
void UnloadLibrary(void* handle);