#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>

#include "yaml-cpp/yaml.h"

namespace cp {

class TDagJobExecutor;

struct TJob {
    std::string name, path;
};

class TJobDag {
private:
    using TMapStringToStrings = std::map<std::string, std::vector<std::string>>;

    // Common rule :
    // if the pair represents dependency then first element is what REQUIRED and the second one is TARGET
    // Map of jobs
    std::map<std::string, TJob> jobs;

    // Map of dependencies. dep["name"] gives us vector of jobs REQUIRED to do job "name"
    TMapStringToStrings dep;

    // Inversed dep. dep^-1
    TMapStringToStrings rdep;

    std::vector<std::string> mutexes;
    // Map of mutexes, each job own : mutOwn[j] is vector of mutexes, which j own
    TMapStringToStrings mutOwn;

    // 0 - not-visited, 1 - in current route, 2 - visited and not in current route
    // returns true if have loops, false - otherwise
    static bool Dfs(const std::string &v,
                    std::map<std::string, int>& visited,
                    TMapStringToStrings& dep);

    static bool CheckCorrectness(TJobDag &dag);

    static TMapStringToStrings Inverse(TMapStringToStrings &map);

public:

    friend class TDagJobExecutor;

    TJobDag() = default;
    TJobDag(const std::vector<TJob>& jobs,
            const std::vector<std::pair<std::string, std::string>>& deps,
            const std::vector<std::string>& _mutexes = {},
            const TMapStringToStrings& _mutOwn = {});

};

class YAMLParser {
public:

    static TJobDag Parse(const std::string &pathToFile);

};

} // namespace cp
