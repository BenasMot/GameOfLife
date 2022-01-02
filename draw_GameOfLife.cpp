#include <SDL.h>
#include <cstdio>
#include <iostream>

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800
#define GRID_SIZE 20
#define CELL_SIZE 20

void initialize(void);
void terminate(int exit_code);
void handle_input(void);

void draw_grid(void);
void draw_cell(int x, int y);
void display_generation(void);

typedef struct {
  SDL_Renderer *renderer;
  SDL_Window *window;
  int running;
  int generation;
} Game;

// initialize global structure to store game state
// and SDL renderer for use in all functions
Game game = {
  .running = 1,
  .generation = 0
};

int main() {
  // Initialize SDL and the relevant structures
  initialize();

  // enter game loop
  while (game.running) {
    // clear the screen with all black before drawing anything 
    SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
    SDL_RenderClear(game.renderer);
    
    // make so that if ESC is pressed the game closes
    handle_input();
    
    // draw the grid lines
    draw_grid();

    // draw the cell(s)
    for (int i = 0; i < 5; i++){
      draw_cell(500 + i*CELL_SIZE, 600 + i*CELL_SIZE);
      //display_generation();
      game.generation++;
    }
    
    // update the screen with any rendering performed since the previous call
    SDL_RenderPresent(game.renderer);
    
    // wait <...> (right now -> zero) milliseconds before next iteration
    // SDL_Delay(0);
  }

  cout << "Total generations: " << game.generation << endl;

  // make sure program cleans up on exit
  terminate(EXIT_SUCCESS);
}

void initialize() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("error: failed to initialize SDL: %s\n", SDL_GetError());
    terminate(EXIT_FAILURE);
  }

  // create the game window
  game.window = SDL_CreateWindow("Generation: 0", 
    SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, 
    SCREEN_WIDTH, 
    SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN
  );

  if (!game.window) {
    printf("error: failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
    terminate(EXIT_FAILURE);
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);

  if (!game.renderer) {
    printf("error: failed to create renderer: %s\n", SDL_GetError());
    terminate(EXIT_FAILURE);
  }
}

void terminate(int exit_code) {
  if (game.renderer) {
    SDL_DestroyRenderer(game.renderer);
  }
  if (game.window) {
    SDL_DestroyWindow(game.window);
  }
  SDL_Quit();
  exit(exit_code);
}

void handle_input() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    // change the game state to not running when close or the esc key is pressed
    // so that the game loop is exited in main
    if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
      game.running = 0;
    }
  }
}

void draw_grid(void) {
  // grid color set to gray
  SDL_SetRenderDrawColor(game.renderer, 44, 44, 44, 255);

  // vertical lines
  for (int grid_x = 0; grid_x < 1 + SCREEN_HEIGHT*2; grid_x += GRID_SIZE) {
      SDL_RenderDrawLine(game.renderer, grid_x, 0, grid_x, SCREEN_HEIGHT);
  }

  // horizontal lines
  for (int grid_y = 0; grid_y < 1 + SCREEN_WIDTH; grid_y+= GRID_SIZE) {
      SDL_RenderDrawLine(game.renderer, 0, grid_y, SCREEN_WIDTH, grid_y);
  }
}

void draw_cell(int x, int y) {
  SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);

  SDL_Rect cell = {
        .x = 0,
        .y = 0,
        .w = CELL_SIZE,
        .h = CELL_SIZE
  };

  cell.x = x;
  cell.y = y;
  SDL_RenderFillRect(game.renderer, &cell);
}

void display_score(void) {
  char buffer [49];
  sprintf(buffer, "Generation: %d", game.generation);
  SDL_SetWindowTitle(game.window, buffer);
}