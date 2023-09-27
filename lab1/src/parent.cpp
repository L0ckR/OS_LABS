#include <parent.hpp>


void parentProcess(std::string pathToChild, std::istream & streamIn, std::ostream & streamOut ){
    std::cin.rdbuf(streamIn.rdbuf());
    std::cout.rdbuf(streamOut.rdbuf());
    
    int CHILD_STDOUT[2];
    createPipe(CHILD_STDOUT);

    int CHILD_STDIN[2];
    createPipe(CHILD_STDIN);
    pid_t pid = createChild();
    
    

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
        
        exec(pathToChild);
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
        
        std::stringstream output = read_from_pipe(CHILD_STDOUT[READ_END]);

        while(std::getline(output, line)){
            std::cout << line << std::endl;
        }

        
        close(CHILD_STDOUT[READ_END]);
        //exit(EXIT_SUCCESS);

    }
}