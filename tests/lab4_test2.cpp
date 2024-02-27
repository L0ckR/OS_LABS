#include <gtest/gtest.h>

#include <iostream>
#include <algorithm>

extern "C" {
    #include "implementations.hpp"
}

constexpr const float EPS = 1e-6;

bool EqualFloat(float lhs, float rhs) {
    return std::abs(lhs - rhs) < EPS;
}

TEST(Lab4, SinIntegralStaticTest1) {
    float result = SinIntegral(0, PI, 0.01);
    EXPECT_NEAR(result, 2, 0.001);
}

TEST(Lab4, SinIntegralStaticTest2) {
    float result = SinIntegral(0, PI/2, 0.01);
    EXPECT_NEAR(result, 1, 0.001);
}

TEST(Lab4, SinIntegralStaticTest3) {
    float result = SinIntegral(0, PI/3, 0.01);
    EXPECT_NEAR(result, 0.5, 0.001);
}

TEST(Lab4, SortTestLib2) {
    srand(time(NULL));
    const int N = 100;
    int a[N];
    for (int i = 0; i < N; i++) {
        a[i] = rand();
    }
    Sort(a, N);
    EXPECT_TRUE(std::is_sorted(a, a + N));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}