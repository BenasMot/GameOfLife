#include <map>
#include <utility>

#include "Types.hpp"

using namespace std;

class GameOfLife {
 private:
  Grid state;
  void updateAllNearbyCellCounts();

 public:
  GameOfLife(){};
  ~GameOfLife(){};

  //Getters
  Grid getState();

  // Actions
  void initialize(Grid init);
  void addCell(Coords coords);
  void removeCell(Coords coords);
  void update();
};

// Utils
vector<Coords> getNeighboursCoords(Coords coords) {
  vector<Coords> neighbourCoords;
  for (int i = -1; i <= 1; i++) {
    auto x = coords.first + i;
    for (int j = -1; j <= 1; j++) {
      auto y = coords.second + j;
      if (!(i == 0 && j == 0)) {
        neighbourCoords.push_back(pair{x, y});
      }
    }
  }
  return neighbourCoords;
}

Grid createNeighnours(Coords coords) {
  Grid neighbours;
  for (auto neigbourCoords : getNeighboursCoords(coords)) {
    neighbours[neigbourCoords] = new Cell(false);
  }
  return neighbours;
}

bool cellShouldBeRemoved(Cell *cell) { return (!cell->getIsAlive() && cell->getNearbyCells() <= 0); }

// Getters
Grid GameOfLife::getState() { return state; }

// Actions
void GameOfLife::updateAllNearbyCellCounts() {
  for (auto cell : this->state) {
    Coords coords = cell.first;
    if (cell.second->getIsAlive()) {
      for (auto neighbourCoords : getNeighboursCoords(coords)) {
        this->state[neighbourCoords]->increaseNearbyCells();
      }
    }
  }
  for (auto cell : this->state) {
    cell.second->updateNearby();
  }
}

void GameOfLife::initialize(Grid init) {
  this->state = init;
  for (auto cell : init) {
    this->state.merge(createNeighnours(cell.first));
  }
  updateAllNearbyCellCounts();
}

void GameOfLife::addCell(Coords coords) {
  bool isNotInitialized = state.count(coords) == 0;

  if (isNotInitialized) {
    state[coords] = new Cell();
    state[coords]->setWillAppear();
  } else if (!state[coords]->getIsAlive()) {
    state[coords]->setWillAppear();
  } else {
    return;
  }
  
  state.merge(createNeighnours(coords));
  for (auto neighbourCoords : getNeighboursCoords(coords)) {
    state[neighbourCoords]->increaseNearbyCells();
  }
}

void GameOfLife::removeCell(Coords coords) {
  bool isNotInitialized = state.count(coords) == 0;

  if (isNotInitialized) {
    return;
  } else if (state[coords]->getIsAlive()) {
    state[coords]->setWillDie();
    for (auto neighbourCoords : getNeighboursCoords(coords)) {
      bool isNeighbourInitialized = state.count(neighbourCoords) != 0;
      if (isNeighbourInitialized) state[neighbourCoords]->increaseNearbyCells(-1);
    }
  }
}

void GameOfLife::update() {
  for (auto cell : this->state) {
    auto nearbyCellCount = cell.second->getNearbyCells();
    bool isAlive = cell.second->getIsAlive();

    if (isAlive) {
      if (nearbyCellCount < 2) {
        removeCell(cell.first);
      } else if (nearbyCellCount >= 4) {
        removeCell(cell.first);
      }
    } else {
      if (nearbyCellCount == 3) {
        addCell(cell.first);
      }
    }
  }

  for (auto cell : this->state) {
    Cell *cellInstance = cell.second;
    if (cellInstance->getWillDie()) cellInstance->die();
    if (cellInstance->getWillAppear()) cellInstance->appear();
    cellInstance->updateNearby();
  }

  for (auto cell : this->state) {
    Coords coords = cell.first;
    if (cellShouldBeRemoved(state[coords])) {
      state.erase(coords);
    }
  }
}