#ifndef M1_CPP_PROJECT_TO_STRING
#define M1_CPP_PROJECT_TO_STRING

#include "Environnement.h"
#include <iostream>
#include <vector>

std::ostream &operator<<(std::ostream &out, const Wall &w);

std::ostream &operator<<(std::ostream &out, const std::vector<Wall> &v);


#endif