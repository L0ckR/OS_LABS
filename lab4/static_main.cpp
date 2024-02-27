#include "implementations.hpp"

#include <iostream>

void Task(const std::string& command) {
    if (command == "1") {
        float arg1, arg2, arg3;
        std::cin >> arg1 >> arg2 >> arg3;
        float result = SinIntegral(arg1, arg2, arg3);
        std::cout << "Result of integral = " << result << std::endl;
    } else if (command == "2") {
        std::cout << "Sort function" << std::endl;
        std::cout << "Enter size of array:" << std::endl;
        size_t size;
        std::cin >> size;
        std::cout << "Enter members of array:" << std::endl;
        int *arr = new int[size];
        for (size_t i = 0; i < size; i++) { 
            std::cin >> arr[i]; 
        } 
        int *result = Sort(arr, size);
        for (size_t i = 0; i < size; i++) { 
            std::cout << result[i] << " "; 
        } 
        std::cout << std::endl;
    } else {
        std::cout << "Invalid command" << std::endl;
    }
}

int main() {
    std::string command;
    while(true) {
        std::cout << "Enter the command (0 - exit): ";
        std::cin >> command;
        if (command == "0") {
            break;
        }
        Task(command);
    }
    return 0;
}