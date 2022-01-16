#include <omp.h>

#include <deque>
#include <iostream>

#include "src/Cell.hpp"
#include "src/GameOfLife.hpp"
#include "src/Timer.hpp"
#include "src/Types.hpp"
#include "src/draw.hpp"

using namespace std;

// Examples of various states

// string state = "+";

// string state =  // Pulsar
//     "--+++---+++--\n"
//     "-------------\n"
//     "+----+-+----+\n"
//     "+----+-+----+\n"
//     "+----+-+----+\n"
//     "--+++---+++--\n"
//     "-------------\n"
//     "--+++---+++--\n"
//     "+----+-+----+\n"
//     "+----+-+----+\n"
//     "+----+-+----+\n"
//     "-------------\n"
//     "--+++---+++--\n";

// string state = // The R-pentonimo
//     "---++--\n"
//     "--++---\n"
//     "---+---\n"
//     "-------";

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

// string state =  // Gosper glider gun 8)
//     "--------------------------------------\n"
//     "-------------------------+------------\n"
//     "-----------------------+-+------------\n"
//     "-------------++------++------------++-\n"
//     "------------+---+----++------------++-\n"
//     "-++--------+-----+---++---------------\n"
//     "-++--------+---+-++----+-+------------\n"
//     "-----------+-----+-------+------------\n"
//     "------------+---+---------------------\n"
//     "-------------++-----------------------\n"
//     "--------------------------------------";

string state =  // glider
    "--+\n"
    "+-+\n"
    "-++\n";

Grid parseInit(string input);
void renderState(Grid grid);

int main() {
  bool isPeriodic = true;
  int genLimit = 1500;
  int worldX = 7;
  int worldY = 7;

  initializeApp();

  GameOfLife game(Coords(worldX, worldY), isPeriodic);
  game.initialize(parseInit(state));

  Timer timer;
  timer.start();
  while (app.running && (app.generation++ < genLimit - 1) && (!game.getShouldStop())) {
    renderState(game.getState());
    game.update();
    timer.setTimeout(200);
  }
  timer.stop();

  while (app.running) {
    renderState(game.getState());
    timer.setTimeout(500);
  }

  cout << "Total generations: " << app.generation << endl;
  cout << "Time elapsed: " << timer.get_elapsed() / 1e6 << endl;

  terminate(EXIT_SUCCESS);
}

void renderState(Grid grid) {
  SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
  SDL_RenderClear(app.renderer);

  draw_grid();
  draw_cells(grid);

  display_generation();
  handle_input();
  SDL_RenderPresent(app.renderer);
}

Grid parseInit(string input) {
  Grid init;
  int xOffset = 0;
  int x = xOffset, y = 0;

  for (auto chr : input) {
    if (chr == '+') {
      init.push_back(Cell(Coords(x, y), true));
    } else if (chr == '\n') {
      y++;
      x = xOffset - 1;
    }
    x++;
  }

  return init;
}
