#include <omp.h>

#include <iostream>
#include <map>

#include "src/GameOfLife.hpp"
#include "src/Types.hpp"

using namespace std;

string state =  "---++--\n"
                "--+--+-\n"
                "--+-+--\n"
                "---++--"; 

Grid parseInit(string input);
void logState(Grid grid);

int main() {
  GameOfLife game;
  game.initialize(parseInit(state));

  logState(game.getState());
  for (int i = 0; i < 1; i++) {
    game.update();
    logState(game.getState());
  }

  return 0;
}

void logState(Grid grid) {
  int x_max = 12, y_max = 12;
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

Grid parseInit(string input) {
  Grid init;
  int x = 0, y = 0;

  for (auto chr : input) {
    if (chr == '+') {
      init[pair{x, y}] = new Cell(true);
    } else if (chr == '\n') {
      y++;
      x = -1;
    }
    x++;
  }

  return init;
}
