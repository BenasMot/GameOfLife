#include <omp.h>

#include <iostream>
#include <map>

#include "src/GameOfLife.hpp"
#include "src/Types.hpp"

using namespace std;

int main() {
  GameOfLife game;
  
  Grid init;
  init[make_pair(1,1)] = new Cell(true);
  init[make_pair(1,2)] = new Cell(true);
  init[make_pair(1,3)] = new Cell(true);
  game.initialize(init);

  game.addCell(make_pair(2,2));

  Grid a = game.getCells();
  for (auto cell:a){
    cout << "[" << cell.first.first << ", " << cell.first.second << "] " << cell.second->getIsAlive() << endl;
  }

  return 0;
}