#include "implementations.hpp"
#include <vector>

extern "C" void swap(int* lhs, int* rhs) {
    int c = *lhs;
    *lhs = *rhs;
    *rhs = c;
}


extern "C" float SinIntegral(float a, float b, float e) {
    float integral = 0.0;
    e = (b - a) / NUM_POINTS;
    for (int i = 1; i < NUM_POINTS; ++i) {
        float x1 = a + i * e;
        float x2 = a + (i + 1) * e;
        integral += 0.5 * e * (sin(x1) + sin(x2));
    }
    return integral;
}

extern "C" void QuickSort(int* array, int first, int last) {
    int i = first, j = last, x = array[(first + last) / 2];

    do {
        while (array[i] < x) i++;
        while (array[j] > x) j--;

        if(i <= j) {
            if (array[i] > array[j]) swap(&array[i], &array[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last) {
        QuickSort(array, i, last);
    }
    if (first < j) {
        QuickSort(array, first, j);
    }
}

extern "C" int * Sort(int * array, size_t size){
    if (size == 1 || size == 0) {
        return array;
    }
    QuickSort(array, 0, size - 1);
    return array;
}