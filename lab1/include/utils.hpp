#ifndef INC_1_UTILS_H
#define INC_1_UTILS_H

#include <sstream>
#include <algorithm>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <ext/stdio_filebuf.h>

enum PipeEnd {
    READ_END,
    WRITE_END
};

void createPipe(int pipeFd[2]);
pid_t createChild();
void exec(std::string pathToChild);
std::stringstream read_from_pipe(int file_descriptor);
bool BothAreSpaces(char lhs, char rhs);


#endif //INC_1_UTILS_H