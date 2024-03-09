#include "utils.hpp"

int main() {
    const char *pathToLib1 = getenv("PATH_TO_LIB1");
    const char *pathToLib2 = getenv("PATH_TO_LIB2");
    // bash: export PATH_TO_LIB1="/home/lockr/projects/OS_LABS/build/lab4/liblib1.so"
    // bash: export PATH_TO_LIB2="/home/lockr/projects/OS_LABS/build/lab4/liblib2.so"

    void* libraryHandle = LoadLibrary(pathToLib1);
    SinIntegralFunc SinIntegral = (SinIntegralFunc)dlsym(libraryHandle, "SinIntegral");
    SortFunc Sort = (SortFunc)dlsym(libraryHandle, "Sort");

    std::string command;
    while(true) {
        std::cout << "Enter the command (0 - switch implementation, e - exit): ";
        std::cin >> command;
        if (command == "e") {
            break;
        } else if (command == "0") {
            std::cout << "Enter the library (1 or 2): ";
            std::cin >> command;
            if (command == "1") {
                libraryHandle = LoadLibrary(pathToLib1);
            } else if (command == "2") {
                libraryHandle = LoadLibrary(pathToLib2);
            } else {
                std::cout << "Invalid library" << std::endl;
            }
            SinIntegral = (SinIntegralFunc)dlsym(libraryHandle, "SinIntegral");
            Sort = (SortFunc)dlsym(libraryHandle, "Sort");
        } else {
            if (command == "1") {
                std::cout << "SinIntegral function:" << std::endl;
                float arg1, arg2, arg3;
                std::cin >> arg1 >> arg2 >> arg3;
                float result = SinIntegral(arg1, arg2, arg3);
                std::cout << "Result of integral = " << result << std::endl;
            } else if (command == "2") {
                std::cout << "Sort function:" << std::endl;
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
    }
    UnloadLibrary(libraryHandle);
    return 0;
}