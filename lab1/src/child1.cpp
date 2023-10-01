#include <string>
#include <iostream>
#include <algorithm>


int main(){
    std::string line;
    while(std::getline(std::cin, line)){
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        std::cout << line << std::endl;
    }
    exit(EXIT_SUCCESS);
}