#include <utils.hpp>


pid_t CreateChild(){
    pid_t pid = fork();
    if( pid < 0 ){
        std::perror("Couldn't create child.");
        exit(EXIT_FAILURE);
    }
    return pid;
}


void CreatePipe(int pipeFd[2]){
    if( pipe(pipeFd) < 0 ) {
        std::perror("Couldn't create pipe.");
        exit(EXIT_FAILURE);
    }
}

void Exec(std::string pathToChild){
    if (execl(pathToChild.c_str(), "child", NULL) == -1) {
        perror("Failed to exec.");
        exit(EXIT_FAILURE);
    }
}


std::stringstream ReadFromPipe (int file_descriptor)
{
  __gnu_cxx::stdio_filebuf<char> filebuf(file_descriptor, std::ios_base::in);

  std::stringstream stream;
  
  stream << &filebuf;
  return stream;
}


bool BothAreSpaces(char lhs, char rhs){ 
            return (lhs == rhs) && (lhs == ' '); 
};