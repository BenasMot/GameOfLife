#ifndef CELL_H
#define CELL_H

#include <utility>

// each cell has a pair of coordinates and a boolean to show if it's alive
struct Cell {
  std::pair<int, int> coordinates;
  bool isAlive;
  Cell(std::pair<int, int> coords, bool alive) {
    coordinates = coords;
    isAlive = alive;
  };
  bool operator==(const Cell &cell) const { return (coordinates == cell.coordinates && isAlive == cell.isAlive); }
};

#endif
