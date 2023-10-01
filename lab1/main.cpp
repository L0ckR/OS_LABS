#include "parent.hpp"


int main(void) {


    ParentProcess(getenv("PATH_TO_CHILD1"), getenv("PATH_TO_CHILD2"), std::cin, std::cout);

    exit(EXIT_SUCCESS);
}
