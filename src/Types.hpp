#pragma once
#include <map>
#include <utility>

#include "Cell.hpp"
using Coords = pair<int, int>;
using Grid = std::map<Coords, Cell*>;
