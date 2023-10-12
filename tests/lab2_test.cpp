#include <gtest/gtest.h>

#include <chrono>
#include <matplot/matplot.h>

#include <monte-carlo.hpp>

double getAvgTime(int threadCount) {
        constexpr int runsCount = 5;

        double avg = 0;

        for(int i = 0; i < runsCount; ++i) {
            auto begin = std::chrono::high_resolution_clock::now();
            CircleArea(threadCount, 5, 100000000);
            auto end = std::chrono::high_resolution_clock::now();
            avg += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        }

        return avg / runsCount;
};


TEST(FirstLabTests, DotsQuantityTest) {
    double area = M_PI*(5*5);
    for (size_t i = 10; i <= 100; i++){
        double areaMonteCarlo = CircleArea(10, 5, 10000*i);
        EXPECT_LE(area - 1, areaMonteCarlo);
        EXPECT_LE(areaMonteCarlo, area + 1);
    }
}

TEST(FirstLabTests, ThreadCountTest) {
    double area = M_PI*(5*5);
    for (size_t threadCount = 1; threadCount <= 12; threadCount++){
        double areaMonteCarlo = CircleArea(threadCount, 5, 100000);
        ASSERT_TRUE(area - 1 <= areaMonteCarlo);
        ASSERT_TRUE(areaMonteCarlo <= area + 1);
    }
}

TEST(FirstLabTests, TimeComparasion){
    std::vector<double> x(12);
    for (int i = 0; i <= 12; ++i) {
        auto current = getAvgTime(i);
        x.push_back(current);

        std::cout << "Avg time for " << i <<" threads: " << current << std::endl;

    }
    matplot::stairs(x);
    
    matplot::show();
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    std::cout.precision(15);
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    
    return RUN_ALL_TESTS();
    
}
