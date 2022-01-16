#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <deque>
#include <iostream>

#include "Cell.hpp"
#include "Timer.hpp"
#include "Types.hpp"

class GameOfLife {
 private:
  Coords worldSize;
  bool isPeriodic;
  World world;
  World worldNext;
  Grid state;
  std::deque<World> worldHistory;
  bool shouldStop;

  // Utils
  Coords handleWorldLimits(Coords coords);
  bool getWorldCell(Coords coords);
  void setWorldCell(Coords coords, bool isAlive);
  Coords worldIndexToCoords(int index);
  bool invalidCoords(Coords coords);
  void ensureEndRules();

 public:
  GameOfLife(Coords size, bool isPeriodic);

  // Getters
  Grid getState();
  bool getShouldStop();

  // Actions
  void initialize(Grid init);
  void update();
};

// Constructor
GameOfLife::GameOfLife(Coords size, bool periodic) {
  shouldStop = false;

  worldSize = size;
  isPeriodic = periodic;

  world = World(size.first * size.second);
  worldNext = World(size.first * size.second);

  state.reserve(size.first * size.second);
}

// Utils
Coords GameOfLife::handleWorldLimits(Coords coords) {
  if (isPeriodic) {
    int x = (coords.first + worldSize.first) % worldSize.first;
    int y = (coords.second + worldSize.second) % worldSize.second;
    return Coords(x, y);
  }

  return coords;
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

bool GameOfLife::invalidCoords(Coords coords) {
  return (coords.first > worldSize.first || coords.first < 0 || coords.second > worldSize.second || coords.second < 0);
}

void GameOfLife::ensureEndRules() {
  // shouldStop = (state.size() == 0);

  if (worldHistory.size() != 1) shouldStop = (worldHistory[0] == worldHistory[worldHistory.size()]);


  for (int i = 0; i < worldNext.size(); ++i) {
    std::cout << worldNext[i];
    if (i % worldSize.first == 0) std::cout << "\n";
  }
  std::cout << std::endl;
  // if (worldHistory.size() != 1) {
  //   std::cout << (worldHistory[0] == worldHistory[worldHistory.size()]) << std::endl;
  //   std::cout << worldHistory.size() << std::endl;
  // }
}

// Getters
Grid GameOfLife::getState() { return state; }
bool GameOfLife::getShouldStop() { return shouldStop; }

// Actions
void GameOfLife::initialize(Grid init) {
  state = init;

  for (Cell cell : init) {
    setWorldCell(handleWorldLimits(cell.coordinates), cell.isAlive);
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
        if (!invalidCoords(correctedCoords)) {
          aliveNearby += getWorldCell(correctedCoords);
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
    }
#pragma omp critical
    state.insert(state.end(), nextState.begin(), nextState.end());
  }

  if (worldHistory.size() == 30) worldHistory.pop_front();
  worldHistory.push_back(worldNext);

  // #pragma omp critical
  ensureEndRules();
  world.swap(worldNext);
}

#endif
