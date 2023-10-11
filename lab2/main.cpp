#include <monte-carlo.hpp>



int main(int argc, char const *argv[])
{
    if (argc != 2){
        std::cout << "wrong arguments" << std::endl;
        return -1;
    }
    std::cout.precision(15);
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);

    long threadQuantity = strtol(argv[1], nullptr, 10);

    double radius;
    size_t dotsQuantity;
    std::cin >> radius;
    std::cin >> dotsQuantity;

    std::cout << CircleArea(threadQuantity, radius, dotsQuantity) << std::endl;
    
    return 0;
}

