#include "parent.hpp"
#include "utils.hpp"

void ParentProcess(const char * pathToChild1, const char * pathToChild2, std::istream & streamIn, std::ostream & streamOut){
    const char* name1 = "/shm1";
    const char* name2 = "/shm2";
    const char* name3 = "/shm3";
    

    pid_t pid = CreateFork();
    if (pid == 0) { // child 1
        if (execlp(pathToChild1, "child1", name1, name2, nullptr) == -1) {
            std::cerr << "Failed execlp()\n";
            exit(-5);
        }
    }else {
        pid = CreateFork();
        if (pid == 0) { // child 2
            if (execlp(pathToChild2, "child2", name2, name3, nullptr) == -1) {
                std::cerr << "Failed execlp()\n";
                exit(-5);
            }
        } else { //parent
            sem_t *semptr1 = CreateSemaphore(SEM_1, 0);
            int shd_fd1 = CreateShm(name1);
            char *memptr1 = MapSharedMemory(FILE_SIZE, shd_fd1);

            sem_t *semptr2 = CreateSemaphore(SEM_2, 0);
            int shd_fd2 = CreateShm(name2);
            char *memptr2 = MapSharedMemory(FILE_SIZE, shd_fd2);

            sem_t *semptr3 = CreateSemaphore(SEM_3, 0);
            int shd_fd3 = CreateShm(name3);
            char *memptr3 = MapSharedMemory(FILE_SIZE, shd_fd3);
            int status;
            std::string line;
            while (std::getline(streamIn, line)) {
                line += '\n';
                strcpy(memptr1, line.c_str());
                sem_post(semptr1);
                sem_wait(semptr3);
                std::string_view st(memptr3);
                std::string s = {st.begin(), st.end()};
                streamOut << s;
                strcpy(memptr3, "\n");
            }
            strcpy(memptr1, "\0");
            sem_post(semptr1);
            streamOut << "";

            waitpid(-1, &status, 0);
            waitpid(-1, &status, 0);

            sem_close(semptr1);
            sem_unlink(SEM_1);
            shm_unlink("/shm1");
            munmap(memptr1, FILE_SIZE);
            close(shd_fd1);

            sem_close(semptr2);
            sem_unlink(SEM_2);
            shm_unlink("/shm2");
            munmap(memptr2, FILE_SIZE);
            close(shd_fd2);

            sem_close(semptr3);
            sem_unlink(SEM_3);
            shm_unlink("/shm3");
            munmap(memptr3, FILE_SIZE);
            close(shd_fd3);
        }
    }
    return;
}