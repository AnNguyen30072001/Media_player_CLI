#include <stdio.h> /* printf and fprintf */

#ifdef _WIN32
#include <SDL/SDL.h> /* Windows-specific SDL2 library */
#else
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#endif

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600
#define DELAY 5000

// g++ temp.cpp -o temp -lSDL2 -lSDL2_mixer -pthread -lavformat

int main (int argc, char **argv)
{
  /* Initialises data */
  SDL_Window *window = NULL;
  
  //The surface contained by the window
  SDL_Surface* screenSurface = NULL;
  
  /*
  * Initialises the SDL video subsystem (as well as the events subsystem).
  * Returns 0 on success or a negative error code on failure using SDL_GetError().
  */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
    return 1;
  }

  /* Creates a SDL window */
  window = SDL_CreateWindow("SDL Example", /* Title of the SDL window */
			    SDL_WINDOWPOS_UNDEFINED, /* Position x of the window */
			    SDL_WINDOWPOS_UNDEFINED, /* Position y of the window */
			    WIDTH, /* Width of the window in pixels */
			    HEIGHT, /* Height of the window in pixels */
			    SDL_WINDOW_SHOWN); /* Additional flag(s) */

  /* Checks if window has been created; if not, exits program */
  if (window == NULL) {
    fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
    return 1;
  }

  screenSurface = SDL_GetWindowSurface( window );
  SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
  SDL_UpdateWindowSurface( window );


  /* Pauses all SDL subsystems for a variable amount of milliseconds */
  SDL_Delay(DELAY);

  /* Frees memory */
  SDL_DestroyWindow(window);
  
  /* Shuts down all SDL subsystems */
  SDL_Quit(); 
  
  return 0;
}