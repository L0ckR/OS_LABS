#include <utils.hpp>


int main(){

    int fd[2];
    createPipe(fd);

    pid_t pid = createChild();
    

    if (pid == pid_t(0)){
        close(fd[READ_END]);


        std::string line;
        while(std::getline(std::cin, line)){
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            line += "\n";
            write(fd[WRITE_END], line.c_str(), line.length());
        }
        close(fd[WRITE_END]);

        exit(EXIT_SUCCESS);
    }else{
        
        close(fd[WRITE_END]);

        wait(NULL);


        std::stringstream output = read_from_pipe(fd[READ_END]);

        std::string line;

        while (std::getline(output, line)){

            std::string::iterator new_end = std::unique(line.begin(), line.end(), BothAreSpaces);
            line.erase(new_end, line.end());

            std::cout << line << "\n";   
        }

        
        close(fd[READ_END]);
        exit(EXIT_SUCCESS);
        
    }
}

// #include <utils.hpp>


// int main(){
//     std::string line;
//     while(std::getline(std::cin, line)){
//         std::cout << line<< std::endl;
//     }
//     // int fd[2];
//     // createPipe(fd);

//     // pid_t pid = createChild();
    

//     // if (pid == pid_t(0)){
//     //     close(fd[READ_END]);
// }
