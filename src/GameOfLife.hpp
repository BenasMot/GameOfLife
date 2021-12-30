#include <map>
#include <utility>

#include "Types.hpp"

using namespace std;

class GameOfLife {
 private:
  Grid cells;
  void updateAllNearbyCells();

 public:
  GameOfLife();
  ~GameOfLife();
  // Getters
  Grid getCells();
  // Actions
  void initialize(Grid init);
  void addCell(Coords coords);
  void update();
};

GameOfLife::GameOfLife() {}

GameOfLife::~GameOfLife() {}

// Utils
Grid createNeighnours(Coords coords) {
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
    neighbours.merge(createNeighnours(coords));
  }
  this->cells.merge(init);
  this->cells.merge(neighbours);
}

void GameOfLife::addCell(Coords coords) {
  this->cells.insert_or_assign(coords, new Cell(true));
  this->cells.merge(createNeighnours(coords));
}

void GameOfLife::updateAllNearbyCells() {
  for (auto cell : cells) {
    Coords coords = cell.first;
    if (cell.second->getIsAlive()) {
      for (int i = -1; i <= 1; i++) {
        auto x = coords.first + i;
        for (int j = -1; j <= 1; j++) {
          auto y = coords.second + j;
          if (!(i == 0 && j == 0)) {
            this->cells[pair{x,y}]->increaseNearbyCells();
          }
        }
      }
    }
  }
}

void GameOfLife::update() {
  updateAllNearbyCells();
  for (auto cell : cells) {
    if (cell.second->getIsAlive()) {
      
    }
  }
};