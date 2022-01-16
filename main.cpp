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

// string state = "+++";

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

// string state = "++++++++ +++++   +++      +++++++ +++++"; // Pants

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
void renderGameEnd(GameOfLife game);

int main() {
  bool isPeriodic = true;
  int genLimit = 30000;
  int worldX = 255;
  int worldY = 255;
  int maxHistoryLimit = 1700;

  initializeApp();

  GameOfLife game(Coords(worldX, worldY), isPeriodic, maxHistoryLimit);
  game.initialize(parseInit(state));

  Timer timer;
  timer.start();
  while (app.running && (app.generation++ < genLimit - 1) && (!game.getShouldStop())) {
    renderState(game.getState());
    game.update();
  }
  timer.stop();

  renderGameEnd(game);

  cout << "Total generations: " << app.generation << endl;
  cout << "Time elapsed: " << timer.get_elapsed() / 1e6 << endl;
  cout << game.getMessage() << endl;

  terminate(EXIT_SUCCESS);
}

void renderGameEnd(GameOfLife game) {
  while (app.running) {
    renderState(game.getState());
    Timer::setTimeout(500);
  }
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
  int xOffset = 20;
  int x = xOffset, y = 60;

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
