#include "parent.hpp"


int main(void) {
    // export PATH_TO_CHILD1="/home/lockr/projects/OS_LABS/build/lab1/child1"
    // export PATH_TO_CHILD2="/home/lockr/projects/OS_LABS/build/lab1/child2"

    ParentProcess(getenv("PATH_TO_CHILD1"), getenv("PATH_TO_CHILD2"), std::cin, std::cout);

    exit(EXIT_SUCCESS);
}
