#include <iostream>
#include <fstream>

#include "job_dag.hpp"
#include "job_exec.hpp"
using namespace cp;
int main(int argc, char ** argv) {
    if (argc < 2) {
        std::cerr << "Missing arguments : path to config file\n";
        exit(EXIT_FAILURE);
    }

    int maxJobs = 4;
    if (argc > 2) {
        maxJobs = std::atoi(argv[2]);
    }

    std::string pathToConfig(argv[1]);
    TJobDag dag = YAMLParser::Parse(pathToConfig);
    TDagJobExecutor executor(maxJobs);
    executor.Execute(dag);
    std::cout << "Execution finished!\n";
}