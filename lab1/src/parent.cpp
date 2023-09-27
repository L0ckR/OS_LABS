#include <parent.hpp>


void ParentProcess(std::string_view pathToChild1, std::string_view pathToChild2, std::istream & streamIn, std::ostream & streamOut ){
    std::cin.rdbuf(streamIn.rdbuf());
    std::cout.rdbuf(streamOut.rdbuf());
    
    Exec(pathToChild1);

    int CHILD2_STDOUT[2];
    CreatePipe(CHILD2_STDOUT);

    int CHILD1_STDIN[2];
    CreatePipe(CHILD1_STDIN);

    int pipeBetween[2];
    CreatePipe(pipeBetween);


    pid_t pid = CreateChild();
    pid_t pid2 = CreateChild();

    if (pid == pid_t(0)){
        //start of child1 process
        std::cout << pid << " child1" << std::endl;
        close(CHILD1_STDIN[WRITE_END]);
        close(CHILD2_STDOUT[READ_END]);
        close(CHILD2_STDOUT[WRITE_END]);
        close(pipeBetween[READ_END]);
      
        if (dup2(CHILD1_STDIN[READ_END], STDIN_FILENO) == -1){
            perror("dup2 error");
            exit(EXIT_FAILURE);
        }

        if (dup2(pipeBetween[WRITE_END], STDOUT_FILENO) == -1){
            perror("dup2 error");
            exit(EXIT_FAILURE);
        }   
        Exec(pathToChild1);
        //end of child1 process
    }
    else if (pid2 == pid_t(0)){
        std::cout << pid2 << " child2" << std::endl;
        //start of child2 process
        close(CHILD1_STDIN[WRITE_END]);
        close(CHILD1_STDIN[READ_END]);
        close(pipeBetween[WRITE_END]);
        close(CHILD2_STDOUT[READ_END]);
      
        if (dup2(pipeBetween[READ_END], STDIN_FILENO) == -1){
            perror("dup2 error");
            exit(EXIT_FAILURE);
        }

        if (dup2(CHILD2_STDOUT[WRITE_END], STDOUT_FILENO) == -1){
            perror("dup2 error");
            exit(EXIT_FAILURE);
        }   
        Exec(pathToChild2);
        //end of child2 process
    }
    else{
        close(CHILD1_STDIN[WRITE_END]);
        close(CHILD1_STDIN[READ_END]);
        close(pipeBetween[WRITE_END]);
        close(pipeBetween[READ_END]);
        std::cout << pid << " parent " << pid2 << std::endl;

        std::string line;
        while(std::getline(std::cin, line)){
            line += "\n";
            write(CHILD1_STDIN[WRITE_END], line.c_str(), line.length());
        }
        close(CHILD1_STDIN[WRITE_END]);



        wait(NULL);

        std::stringstream output = ReadFromPipe(CHILD2_STDOUT[READ_END]);

        while(std::getline(output, line)){
            std::cout << line << std::endl;
        }

        close(CHILD2_STDOUT[READ_END]);
        //exit(EXIT_SUCCESS); успешный выход из процесса будет осуществлятьcя в main.cpp
    }
}