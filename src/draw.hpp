#ifndef DRAW_H
#define DRAW_H

#include <SDL.h>

#include <cstdio>
#include <string>

#include "Types.hpp"

using namespace std;

#define CELL_SIZE 5
#define GRID_SIZE CELL_SIZE
#define SCREEN_WIDTH 180 * CELL_SIZE
#define SCREEN_HEIGHT 160 * CELL_SIZE
#define X_OFFSET 0
#define Y_OFFSET 0

struct Game {
  SDL_Renderer *renderer;
  SDL_Window *window;
  bool running;
  int generation;
};

// initialize global structure to store app state
// and SDL renderer for use in all functions
Game app = {.running = 1, .generation = 0};

void terminate(int exit_code) {
  // safely terminate the program
  if (app.renderer) {
    SDL_DestroyRenderer(app.renderer);
  }
  if (app.window) {
    SDL_DestroyWindow(app.window);
  }
  SDL_Quit();
  exit(exit_code);
}

void initializeApp() {
  // intialize and error catching if initializing fails
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("error: failed to initialize SDL: %s\n", SDL_GetError());
    terminate(EXIT_FAILURE);
  }

  // create the app window
  app.window = SDL_CreateWindow("Generation: 0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  // error catching
  if (!app.window) {
    printf("error: failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
    terminate(EXIT_FAILURE);
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);

  if (!app.renderer) {
    printf("error: failed to create renderer: %s\n", SDL_GetError());
    terminate(EXIT_FAILURE);
  }
}

void handle_input() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    // change the app state to not running when close or the esc key is pressed
    // so that the app loop is exited in main
    if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
      app.running = 0;
    }
  }
}

void draw_grid(void) {
  // grid color set to gray
  SDL_SetRenderDrawColor(app.renderer, 44, 44, 44, 255);

  // vertical lines
  for (int grid_x = 0; grid_x < 1 + SCREEN_HEIGHT * 2; grid_x += GRID_SIZE) {
    SDL_RenderDrawLine(app.renderer, grid_x, 0, grid_x, SCREEN_HEIGHT);
  }

  // horizontal lines
  for (int grid_y = 0; grid_y < 1 + SCREEN_WIDTH; grid_y += GRID_SIZE) {
    SDL_RenderDrawLine(app.renderer, 0, grid_y, SCREEN_WIDTH, grid_y);
  }
}

void draw_cell(Coords coords, string color = "white") {
  int r, g, b, a = 255;
  if (color == "white") {
    r = g = b = 255;
  } else if (color == "red") {
    r = 255;
    g = b = 0;
  }

  SDL_SetRenderDrawColor(app.renderer, r, g, b, a);

  SDL_Rect cell = {.x = 0, .y = 0, .w = CELL_SIZE, .h = CELL_SIZE};

  cell.x = coords.first * CELL_SIZE + X_OFFSET;
  cell.y = coords.second * CELL_SIZE + Y_OFFSET;

  SDL_RenderFillRect(app.renderer, &cell);
}

void display_generation(void) {
  // update the window title with the generation number, everytime the function's called
  char buffer[49];
  sprintf(buffer, "Generation: %i", app.generation);
  SDL_SetWindowTitle(app.window, buffer);
}

#endif