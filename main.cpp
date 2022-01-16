#include <omp.h>

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

Grid parseInit(string input); // read initial state
void renderState(Grid grid); // render current state

int main() {
  bool isPeriodic = true; // true for periodic grid, false for infinite
  int genLimit = 1500; // generation limit. When reached, it's game over
  int worldX = 255; // X-axis limit for the cells to "live" in
  int worldY = 255; // Y-axis limit for the cells to "live" in
  
  initializeApp(); // start the Game (opens the window)

  GameOfLife game(Coords(worldX, worldY), isPeriodic); // create the "world" in which cells will "live" in
  game.initialize(parseInit(state)); // saves the initial state

  Timer timer;
  timer.start();
  while (app.running && (app.generation++ < genLimit-1) && (game.getAliveCells() > 0)) {
    renderState(game.getState()); // get the current state, then render it
    game.update(); // update the game state
    //timer.setTimeout(200);
  }
  timer.stop();

  // when it's game over, the game doesn't update it's state anymore, only renders it
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
  // make the whole screen black before drawing anything
  SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
  SDL_RenderClear(app.renderer);

  // make so that if ESC or X (on game window) is pressed the game closes
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

  // display current generation on the game window title
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
