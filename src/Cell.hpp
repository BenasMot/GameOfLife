#ifndef CELL_H
#define CELL_H

#include <utility>

struct Cell {
  std::pair<int, int> coordinates;
  bool isAlive;
  Cell(std::pair<int, int> coords, bool alive) {
    coordinates = coords;
    isAlive = alive;
  };
};

#endif
