#pragma once
#include <map>
#include <utility>

#include "Cell.hpp"
using Grid = std::map<std::pair<char, char>, Cell*>;
using Coords = pair<char, char>;