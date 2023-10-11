#include <gtest/gtest.h>

#include <monte-carlo.hpp>

TEST(FirstLabTests, SimpleTest) {
    double area = M_PI*(5*5);
    double areaMonteCarlo = CircleArea(2, 5, 100000000);
    std::cout << area << std::endl;
    std::cout << areaMonteCarlo << std::endl;
    ASSERT_TRUE(area - 1 <= areaMonteCarlo && areaMonteCarlo <= area + 1);
}



TEST(FirstLabTests, TimeTest2vs12) {
    struct timespec start, finish;

    clock_gettime(CLOCK_MONOTONIC, &start);
    CircleArea(12, 5, 100000000);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    double elapsedThreaded = (finish.tv_sec - start.tv_sec);
    elapsedThreaded += (finish.tv_nsec - start.tv_nsec) / 1000000000.0; 

    clock_gettime(CLOCK_MONOTONIC, &start);
    CircleArea(2, 5, 100000000);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    double elapsedNotThreaded = (finish.tv_sec - start.tv_sec);
    elapsedNotThreaded += (finish.tv_nsec - start.tv_nsec) / 1000000000.0; 


    std::cout << elapsedThreaded << " vs. " << elapsedNotThreaded << std::endl;
    ASSERT_TRUE(elapsedThreaded <= elapsedNotThreaded);
}


// TEST(FirstLabTests, TimeTest1vs12) {                                                 // single thread process take less time then multithreaded
//     struct timespec start, finish;                                                   // without multithreading even lesser time

//     clock_gettime(CLOCK_MONOTONIC, &start);
//     CircleArea(12, 5, 100000000);
//     clock_gettime(CLOCK_MONOTONIC, &finish);
//     double elapsedThreaded = (finish.tv_sec - start.tv_sec);
//     elapsedThreaded += (finish.tv_nsec - start.tv_nsec) / 1000000000.0; 

//     clock_gettime(CLOCK_MONOTONIC, &start);
//     CircleArea(1, 5, 100000000);
//     clock_gettime(CLOCK_MONOTONIC, &finish);
//     double elapsedNotThreaded = (finish.tv_sec - start.tv_sec);
//     elapsedNotThreaded += (finish.tv_nsec - start.tv_nsec) / 1000000000.0; 


//     std::cout << elapsedThreaded << " vs. " << elapsedNotThreaded << std::endl;
//     ASSERT_TRUE(elapsedThreaded <= elapsedNotThreaded);
// }



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    std::cout.precision(15);
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);

    return RUN_ALL_TESTS();
}
