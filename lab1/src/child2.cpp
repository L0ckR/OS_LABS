#include <string>
#include <iostream>
#include <algorithm>

bool BothAreSpaces(char lhs, char rhs){ 
            return std::isspace(lhs) && std::isspace(rhs);
};


int main(){
    std::string line;
    while(std::getline(std::cin, line)){
        auto new_end = std::unique(line.begin(), line.end(), BothAreSpaces);
        line.erase(new_end, line.end());
        
        std::cout << line << std::endl;   
    }
    exit(EXIT_SUCCESS);
}