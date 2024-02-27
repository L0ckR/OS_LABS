#include "utils.hpp"

bool BothAreSpaces(char lhs, char rhs){ 
    return (lhs == rhs) && (lhs == ' ');
};

int main (int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Wrong argc in child2\n";
        exit(-6);
    }

    const char* fileName1 = argv[1];
    const char* fileName2 = argv[2];

    sem_t *semptr2 = CreateSemaphore(SEM_2, 0);
    int shd_fd2 = CreateShm(fileName1);
    char *memptr2 = MapSharedMemory(FILE_SIZE, shd_fd2);

    sem_t *semptr3 = CreateSemaphore(SEM_3, 0);
    int shd_fd3 = CreateShm(fileName2);
    char *memptr3 = MapSharedMemory(FILE_SIZE, shd_fd3);

    while(true) {
        sem_wait(semptr2);
        std::string_view st(memptr2);
        std::string s = {st.begin(), st.end()};
        std::string::iterator new_end = std::unique(s.begin(), s.end(), BothAreSpaces);
        s.erase(new_end, s.end());  
        strcpy(memptr3, s.c_str());
        strcpy(memptr2, "\n");
        sem_post(semptr3);


        if (s == "\0") {
            break;
        }
    }

    sem_close(semptr2);
    sem_unlink(SEM_2);
    shm_unlink(fileName1);
    munmap(memptr2, FILE_SIZE);
    close(shd_fd2);

    sem_close(semptr3);
    sem_unlink(SEM_3);
    shm_unlink(fileName2);
    munmap(memptr3, FILE_SIZE);
    close(shd_fd3);

}