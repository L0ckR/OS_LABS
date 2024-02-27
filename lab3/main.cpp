#include "parent.hpp"


int main(void) {
    // export PATH_TO_FM_CHILD1="/home/lockr/projects/OS_LABS/build/lab3/fm_child1"
    // export PATH_TO_FM_CHILD2="/home/lockr/projects/OS_LABS/build/lab3/fm_child2"

    ParentProcess(getenv("PATH_TO_FM_CHILD1"), getenv("PATH_TO_FM_CHILD2"), std::cin, std::cout);

    exit(EXIT_SUCCESS);
}
