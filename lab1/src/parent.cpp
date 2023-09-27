#include <parent.hpp>


void ParentProcess(std::string_view pathToChild, std::istream & streamIn, std::ostream & streamOut ){
    std::cin.rdbuf(streamIn.rdbuf());
    std::cout.rdbuf(streamOut.rdbuf());
    
    int CHILD_STDOUT[2];
    CreatePipe(CHILD_STDOUT);

    int CHILD_STDIN[2];
    CreatePipe(CHILD_STDIN);
    pid_t pid = CreateChild();
    
    

    if (pid == pid_t(0)){
        
        close(CHILD_STDIN[WRITE_END]);
        close(CHILD_STDOUT[READ_END]);
      
        if (dup2(CHILD_STDIN[READ_END], STDIN_FILENO) == -1){
            perror("dup2 error.");
            exit(EXIT_FAILURE);
        }

        if (dup2(CHILD_STDOUT[WRITE_END], STDOUT_FILENO) == -1){
            perror("dup2 error.");
            exit(EXIT_FAILURE);
        }   
        
        Exec(std::string(pathToChild));
    }
    else{
        close(CHILD_STDIN[READ_END]);
        close(CHILD_STDOUT[WRITE_END]);

        std::string line;
        while(std::getline(std::cin, line)){
            line += "\n";
            write(CHILD_STDIN[WRITE_END], line.c_str(), line.length());
        }
        close(CHILD_STDIN[WRITE_END]);
        


        wait(NULL);
        
        std::stringstream output = ReadFromPipe(CHILD_STDOUT[READ_END]);

        while(std::getline(output, line)){
            std::cout << line << std::endl;
        }

        
        close(CHILD_STDOUT[READ_END]);
        //exit(EXIT_SUCCESS); успешный выход из процесса будет осуществлять в main.cpp

    }
}