#ifndef OS_LABS_PARENT_H
#define OS_LABS_PARENT_H

#include <utils.hpp>

void ParentProcess(std::string_view pathToChild1, std::string_view pathToChild2, std::istream & streamIn, std::ostream & streamOut);

#endif //OS_LABS_PARENT_H