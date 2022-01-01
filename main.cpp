#include <omp.h>

#include <iostream>
#include <map>

#include "src/GameOfLife.hpp"
#include "src/Types.hpp"

using namespace std;

int x_max = 6, y_max = 6;
void logState(Grid grid);

int main() {
  GameOfLife game;

  Grid init;
  init[pair{-1, -1}] = new Cell(true);
  init[pair{0, -1}] = new Cell(true);
  init[pair{-2, 0}] = new Cell(true);
  init[pair{1, 0}] = new Cell(true);
  init[pair{-2, 1}] = new Cell(true);
  init[pair{0, 1}] = new Cell(true);
  init[pair{-1, 2}] = new Cell(true);
  init[pair{0, 2}] = new Cell(true);
  game.initialize(init);

  logState(game.getState());
  for (int i = 0; i < 9; i++) {
    game.update();
    logState(game.getState());
  }
  return 0;
}

void logState(Grid grid) {
  cout << "---------" << endl;
  for (int i = -x_max; i < x_max; i++) {
    for (int j = -y_max; j < y_max; j++) {
      if (grid.count(pair{j, i}) != 0) {
        cout << (grid[pair{j, i}]->getIsAlive() ? "⬛️" : "⬜");  //⬜️⬛️🟥
      } else {
        cout << "⬜";
      }
    }
    cout << endl;
  }
  // cout << "---------" << endl;
  // for (int i = -x_max; i < x_max; i++) {
  //   for (int j = -y_max; j < y_max; j++) {
  //     if (grid.count(pair{j, i}) != 0) {
  //       cout << grid[pair{j, i}]->getNearbyCells() << " ";
  //     } else {
  //       cout << "0 ";
  //     }
  //   }
  //   cout << endl;
  // }
  // cout << "---------" << endl;
}