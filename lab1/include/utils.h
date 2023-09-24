//
// Created by retard's pupil on 24.09.23.
//

#ifndef INC_1_UTILS_H
#define INC_1_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum PipeEnd {
    READ_END,
    WRITE_END
};

void CreatePipe(int pipeFd[2]);

char* ReadString(FILE* stream);

#endif //INC_1_UTILS_H