#include "parent.hpp"
//#include <memory>

int main(void) {
    //std::ifstream inFile("input.txt");

    parentProcess("../lab1/child", std::cin, std::cout);
    exit(EXIT_SUCCESS);
}
