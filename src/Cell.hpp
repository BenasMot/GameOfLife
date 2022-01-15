#ifndef CELL_H
#define CELL_H

#include <utility>

struct Cell {
  std::pair<int, int> coordinates; // change to Coords I guess?
  bool isAlive;
  Cell(std::pair<int, int> coords, bool alive) { // same here?
    coordinates = coords;
    isAlive = alive;
  };
};

#endif
