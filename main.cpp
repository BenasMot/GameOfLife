#include <omp.h>

#include <iostream>
#include <map>

#include "src/GameOfLife.hpp"
#include "src/Timer.hpp"
#include "src/Types.hpp"

using namespace std;

string state =
    "---++--\n"
    "--++---\n"
    "---+---\n"
    "-------";

Grid parseInit(string input);
void logState(Grid grid);

int main() {
  Timer timer;
  GameOfLife game;
  game.initialize(parseInit(state));

  logState(game.getState());

  timer.start();
  for (int i = 0; i < 15; i++) {
    game.update();
    // logState(game.getState());
  }
  timer.stop();

  logState(game.getState());

  cout << "Time elapsed: " << timer.get_elapsed() / 1e6 <<  " s" << endl;

  return 0;
}

void logState(Grid grid) {
  int y_max = 30, x_max = 70;
  cout << "---------" << endl;
  for (int i = -30; i < y_max; i++) {
    for (int j = -40; j < x_max; j++) {
      if (grid.count(pair{j, i}) != 0) {
        Cell *cell = grid[pair{j, i}];
        // if (cell->getIsAlive()) {
        //   cout << "\033[1;34m" << cell->getNearbyCells() << cell->getWillDie();
        // } else {
        //   cout << "\033[1;31m" << cell->getNearbyCells() << cell->getWillAppear();
        // }
        cout << (cell->getIsAlive() ? "⬛️" : "🟥");  //⬜️⬛️🟥
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
