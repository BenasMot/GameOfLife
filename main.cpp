#include <omp.h>

#include <iostream>
#include <map>

#include "src/GameOfLife.hpp"
#include "src/Types.hpp"

using namespace std;

int x_max = 12, y_max = 12;
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
  for (int i = 0; i < 18; i++) {
    game.update();
    logState(game.getState());
  }
  return 0;
}

void logState(Grid grid) {
  cout << "---------" << endl;
  for (int i = -4; i < x_max; i++) {
    for (int j = -4; j < y_max; j++) {
      if (grid.count(pair{j, i}) != 0) {
        Cell *cell = grid[pair{j, i}];
        // if (cell->getIsAlive()) {
        //   cout << "\033[1;34m" << cell->getNearbyCells() << cell->getWillDie();
        // } else {
        //   cout << "\033[1;31m" << cell->getNearbyCells() << cell->getWillAppear();
        // }
        cout << (cell->getIsAlive() ? "⬛️" : "⬜️");  //⬜️⬛️🟥
      } else {
        cout << "⬜";
      }
    }
    cout << endl;
  }
}