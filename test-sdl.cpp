#include <SDL.h>

#define SCREEN_WIDTH   680
#define SCREEN_HEIGHT  400
#define CELL_THICKNESS   1

void initialize(void);
void terminate(int exit_code);
void handle_input(void);
void draw_cells(void);

typedef struct {
  SDL_Renderer *renderer;
  SDL_Window *window;
  int running;
} Game;

// initialize global structure to store game state
// and SDL renderer for use in all functions
Game game = {
  .running = 1
};

int main() {
  // Initialize SDL and the relevant structures
  initialize();
  
  // TODO: initialize snake
  // spawn_snake()

  // enter game loop
  while (game.running) {
    // clear the screen with all black before drawing anything 
    SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
    SDL_RenderClear(game.renderer);
    
    handle_input();

    // TODO: add update and draw functions
    // move_snake()
    // draw_food()
    // draw_snake()
    // draw_wall()

    SDL_RenderPresent(game.renderer);
    
    // wait 100 milliseconds before next iteration
    SDL_Delay(0);
  }

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
