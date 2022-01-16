#ifndef TYPES_H
#define TYPES_H

#include <utility>
#include <vector>

#include "Cell.hpp"

using Coords = std::pair<int, int>;
using Grid = std::vector<Cell>;
using World = std::vector<bool>;

#endif
