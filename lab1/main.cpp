#include "parent.hpp"
#include "numeric"

struct BindTwoStrings
{
    std::string operator()(const std::string& s1, const std::string& s2) const {
        return s1.empty() ? s2 : s1 + "\n" + s2;
    }    
};

int main(void) {

    std::vector<std::string> input = {
            "                H",
            "      H    ",
            "h                "
    };

    std::stringstream inFile(std::accumulate(input.begin(), input.end(), std::string(""), BindTwoStrings()));

    std::fstream outFile("out.txt", std::ios_base::out);

    ParentProcess(getenv("PATH_TO_CHILD1"), getenv("PATH_TO_CHILD2"), inFile, outFile);


    //ParentProcess(getenv("PATH_TO_CHILD1"), getenv("PATH_TO_CHILD2"), std::cin, std::cout);

    exit(EXIT_SUCCESS);
}
