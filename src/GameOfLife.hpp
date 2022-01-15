#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "Cell.hpp"
#include "Timer.hpp"
#include "Types.hpp"

class GameOfLife {
 private:
  World world;
  World worldNext;
  Coords worldSize;
  Grid state;
  bool isPeriodic;
  int aliveCells;

  // Utils
  Coords handleWorldLimits(Coords coords);
  bool getWorldCell(Coords coords);
  void setWorldCell(Coords coords, bool isAlive);
  Coords worldIndexToCoords(int index);

 public:
  GameOfLife(Coords size, bool isPeriodic);

  // Getters
  Grid getState();
  int getAliveCells();

  // Actions
  void initialize(Grid init, int numOfCells);
  void update();
};

// Constructor
GameOfLife::GameOfLife(Coords size, bool isPeriodic) {
  worldSize = size;
  world = World(size.first * size.second);
  worldNext = World(size.first * size.second);
  isPeriodic = isPeriodic;
  state.reserve(size.first * size.second);
}

// Utils
Coords GameOfLife::handleWorldLimits(Coords coords) {
  int x, y;
  if (isPeriodic) {
    x = coords.first % worldSize.first;
    y = coords.second % worldSize.second;
  } else {
    if (coords.first > worldSize.first || coords.first < 0) {
      x = -1;
    } else {
      x = coords.first;
    }
    if (coords.second > worldSize.second || coords.second < 0) {
      y = -1;
    } else {
      y = coords.second;
    }
  }
  return Coords(x, y);
}

bool GameOfLife::getWorldCell(Coords coords) {
  auto [x, y] = coords;
  return world[x + y * worldSize.first];
}
void GameOfLife::setWorldCell(Coords coords, bool isAlive) {
  auto [x, y] = coords;
  world[x + y * worldSize.first] = isAlive;
}

Coords GameOfLife::worldIndexToCoords(int index) {
  int x = index % worldSize.first;
  int y = index / worldSize.first;
  return Coords(x, y);
}

std::vector<Coords> getNeighboursCoords(Coords coords) {
  std::vector<Coords> neighbourCoords;
  for (int i = -1; i <= 1; i++) {
    auto x = coords.first + i;
    for (int j = -1; j <= 1; j++) {
      auto y = coords.second + j;
      if (!(i == 0 && j == 0)) {
        neighbourCoords.emplace_back(Coords(x, y));
      }
    }
  }
  return neighbourCoords;
}

// Getters
Grid GameOfLife::getState() { return state; }
int GameOfLife::getAliveCells() { return aliveCells; }

// Actions
void GameOfLife::initialize(Grid init, int numOfCells) {
  state = init;
  aliveCells = numOfCells;

  for (Cell cell : init) {
    Coords coords = handleWorldLimits(cell.coordinates);
    if (coords.first != -1 || coords.second != -1) {
      setWorldCell(handleWorldLimits(cell.coordinates), cell.isAlive);
    }
  }
}

void GameOfLife::update() {
  state.clear();
#pragma omp parallel
  {
    Grid nextState;

#pragma omp for
    for (int i = 0; i < worldSize.first * worldSize.second; ++i) {
      Coords coords = worldIndexToCoords(i);
      int aliveNearby = 0;

      auto neighbours = getNeighboursCoords(coords);
      for (Coords neighbour : neighbours) {
        Coords correctedCoords = handleWorldLimits(neighbour);
        if (correctedCoords.first != -1 && correctedCoords.second != -1) {
          aliveNearby += getWorldCell(handleWorldLimits(neighbour));
        }
      }

      if (world[i]) {
        worldNext[i] = !(aliveNearby < 2 || aliveNearby >= 4);
      } else {
        worldNext[i] = aliveNearby == 3;
      }

      if (worldNext[i]) {
        nextState.emplace_back(Cell(coords, true));
      }

#pragma omp critical
      state.insert(state.end(), nextState.begin(), nextState.end());
    }
  }
  world.swap(worldNext);
}

#endif
