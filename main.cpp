#include <omp.h>

#include <iostream>

#include "src/Cell.hpp"
#include "src/GameOfLife.hpp"
#include "src/Timer.hpp"
#include "src/Types.hpp"
#include "src/draw.hpp"

using namespace std;

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

string state = // Gosper glider gun 8)
    "--------------------------------------\n"
    "-------------------------+------------\n"
    "-----------------------+-+------------\n"
    "-------------++------++------------++-\n"
    "------------+---+----++------------++-\n"
    "-++--------+-----+---++---------------\n"
    "-++--------+---+-++----+-+------------\n"
    "-----------+-----+-------+------------\n"
    "------------+---+---------------------\n"
    "-------------++-----------------------\n"
    "--------------------------------------";

//  string state = // glider
//         "--+\n"
//         "+-+\n"
//         "-++\n";

Grid parseInit(string input);
void renderState(Grid grid);

int main() {
  bool isPeriodic = true;
  int genLimit = 1500;
  int worldX = 255;
  int worldY = 255;
  
  initializeApp();

  GameOfLife game(Coords(worldX, worldY), isPeriodic);
  game.initialize(parseInit(state));

  Timer timer;
  timer.start();
  while (app.running && app.generation++ < genLimit-1 && game.getAliveCells() > 0) {
    renderState(game.getState());
    game.update();
    //timer.setTimeout(200);
  }
  timer.stop();

  while (app.running) {
    renderState(game.getState());
    timer.setTimeout(500);
  }
  cout << "Total generations: " << app.generation << endl;
  cout << "Time elapsed: " << timer.get_elapsed() / 1e6 << endl;

  // make sure program cleans up on exit
  terminate(EXIT_SUCCESS);

  return 0;
}

void renderState(Grid grid) {
  // clear the screen with all black before drawing anything
  SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
  SDL_RenderClear(app.renderer);

  // make so that if ESC is pressed the game closes
  handle_input();

  // draw the grid lines
  draw_grid();

  // draw the cell(s)
  for (auto cell : grid) {
    Coords coords = cell.coordinates;
    if (cell.isAlive) {
      draw_cell(coords);
    } else {
      draw_cell(coords, "red");
    }
  }

  display_generation();
  // update the screen with any rendering performed since the previous call
  SDL_RenderPresent(app.renderer);
}

Grid parseInit(string input) {
  Grid init;
  int xOffset = 25;
  int x = xOffset, y = 50;

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
