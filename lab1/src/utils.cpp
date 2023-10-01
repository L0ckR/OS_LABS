#include <utils.hpp>


pid_t CreateChild(){
    if(pid_t pid = fork(); pid >= 0) {
        return pid;
    }
    std::perror("Couldn't create child.");
    exit(EXIT_FAILURE);   
}


void CreatePipe(int pipeFd[2]){
    if( pipe(pipeFd) < 0 ) {
        std::perror("Couldn't create pipe.");
        exit(EXIT_FAILURE);
    }
}

void Exec(const char * pathToChild){
    if (execl(pathToChild, "child", nullptr) == -1) {
        perror("Failed to exec.");
        exit(EXIT_FAILURE);
    }
}


std::stringstream ReadFromPipe (int file_descriptor){   
    std::stringstream stream;
    
    char ch;

    while (1){
        int state = read(file_descriptor, &ch, sizeof(char));
        if (state > 0){
            stream << ch;
        }else if (state == 0){
            return stream;
        }else{
            perror("Read fail");
            exit(EXIT_FAILURE);
        }
    }

//   ЗАПРЕТНАЯ РЕАЛИЗАЦИЯ
//   __gnu_cxx::stdio_filebuf<char> filebuf(file_descriptor, std::ios_base::in);

//   std::stringstream stream;
  
//   stream << &filebuf;
//   return stream;

}
