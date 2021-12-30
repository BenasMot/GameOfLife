#include <map>
#include <utility>

#include "Types.hpp"

using namespace std;

class GameOfLife {
 private:
  Grid cells;

 public:
  GameOfLife();
  ~GameOfLife();
  // Getters
  Grid getCells();
  // Actions
  void initialize(Grid init);
  void addCell(Coords coords);
};

GameOfLife::GameOfLife() {}

GameOfLife::~GameOfLife() {}

// Utils
Grid getNeighbours(pair<int, int> coords) {
  Grid neighbours;
  for (int i = -1; i <= 1; i++) {
    auto x = coords.first + i;
    for (int j = -1; j <= 1; j++) {
      auto y = coords.second + j;
      if (!(i == 0 && j == 0)) {
        neighbours[make_pair(x, y)] = new Cell(false);
      }
    }
  }
  return neighbours;
}

// Getters
Grid GameOfLife::getCells() { return cells; }

// Actions
void GameOfLife::initialize(Grid init) {
  Grid neighbours;
  for (auto cell : init) {
    auto coords = cell.first;
    neighbours.merge(getNeighbours(coords));
  }
  this->cells.merge(init);
  this->cells.merge(neighbours);
}

void GameOfLife::addCell(Coords coords) {
  this->cells.insert_or_assign(coords, new Cell(true));
  this->cells.merge(getNeighbours(coords));
}
