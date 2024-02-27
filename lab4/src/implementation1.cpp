#include "implementations.hpp"

extern "C" float SinIntegral(float a, float b, float e) {
    float integral = 0.0;
    e = (b - a) / NUM_POINTS;
    for (int i = 0; i <= NUM_POINTS; ++i) {
        integral = integral + e * sin(a + e * (i - 0.5));
    }
    return integral;
}

extern "C" int * Sort(int * array, size_t size){
    if (size == 1 || size == 0) {
        return array;
    }
    for (size_t i = 0; i < size; i++) {
        for (int j = size - 1; j >= 1; j--) {
            if (array[j] < array[j - 1]) {
                int c = array[j];
                array[j] = array[j - 1];
                array[j - 1] = c;
            }
        }
    }
    return array;
}