#pragma once
#include <map>
#include <utility>

#include "Cell.hpp"
using Grid = std::map<std::pair<int, int>, Cell*>;
using Coords = pair<int, int>;