#include <omp.h>

#include <iostream>
#include <map>

#include "src/GameOfLife.hpp"
#include "src/Types.hpp"

using namespace std;

int main() {
  GameOfLife game;

  Grid init;
  init[pair{1, 1}] = new Cell(true);
  init[pair{1, 2}] = new Cell(true);
  init[pair{1, 3}] = new Cell(true);
  game.initialize(init);

  // game.addCell(pair{2, 2});
  game.update();

  int x_max = 6, y_max = 6;
  Grid table;
  for (int i = 0; i < x_max; i++) {
    for (int j = 0; j < y_max; j++) {
      table[pair{i, j}] = new Cell(false);
    }
  }

  Grid a = game.getCells();
  // for (auto cell : a) {
  //   cout << "[" << cell.first.first << ", " << cell.first.second << "] " << cell.second->getIsAlive() << " " << cell.second->getNearbyCells() << endl;
  // }
  a.merge(table);

  cout << "---------" << endl;
  for (int i = 0; i < x_max; i++) {
    for (int j = 0; j < y_max; j++) {
      cout << a[pair{i, j}]->getIsAlive() << " ";
    }
    cout << endl;
  }
  cout << "---------" << endl;
  for (int i = 0; i < x_max; i++) {
    for (int j = 0; j < y_max; j++) {
      cout << a[pair{i, j}]->getNearbyCells() << " ";
    }
    cout << endl;
  }
  cout << "---------" << endl;

  return 0;
}