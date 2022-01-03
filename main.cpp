#include <omp.h>

#include <iostream>
#include <map>

#include "src/GameOfLife.hpp"
#include "src/Timer.hpp"
#include "src/Types.hpp"
#include "src/draw.hpp"

using namespace std;

// string state = // Pulsar
    // "--+++---+++--\n"
    // "-------------\n"
    // "+----+-+----+\n"
    // "+----+-+----+\n"
    // "+----+-+----+\n"
    // "--+++---+++--\n"
    // "-------------\n"
    // "--+++---+++--\n"
    // "+----+-+----+\n"
    // "+----+-+----+\n"
    // "+----+-+----+\n"
    // "-------------\n"
    // "--+++---+++--\n";

string state = // The R-pentonimo
    "---++--\n"
    "--++---\n"
    "---+---\n"
    "-------";

// string state =  // diehard
//     "------+-\n"
//     "++------\n"
//     "-+---+++\n";

// string state = // acorn
//     "-+--------\n"
//     "---+------\n"
//     "++--+++---\n";

// string state =  // npm logo
//     "++++-++++-++++++\n"
//     "++-+-++-+-++-+-+\n"
//     "++-+-++-+-++-+-+\n"
//     "++-+-++++-++-+-+\n"
//     "-----++---------\n";

// string state = "++++++++ +++++   +++      +++++++ +++++";

Grid parseInit(string input);
void logState(Grid grid);

int main() {
  Timer timer;
  GameOfLife game;

  initialize();
  game.initialize(parseInit(state));

  while (app.running) {
    // clear the screen with all black before drawing anything
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);

    // make so that if ESC is pressed the game closes
    handle_input();

    // draw the grid lines
    draw_grid();

    // draw the cell(s)
    for (auto cell : game.getState()) {
      if (cell.second->getIsAlive()) {
        draw_cell(cell.first);
      } else {
        draw_cell(cell.first, "red");
      }
    }

    app.generation++;
    display_generation();

    // update the screen with any rendering performed since the previous call
    SDL_RenderPresent(app.renderer);

    // wait <...> (right now -> zero) milliseconds before next iteration
    // SDL_Delay(0);
    game.update();
    timer.setTimeout(33);
  }

  cout << "Total generations: " << app.generation << endl;

  // make sure program cleans up on exit
  terminate(EXIT_SUCCESS);
  
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
