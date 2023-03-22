// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include "game_sdl.h"
#include "game.h"
#include "game_ext.h"
#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* **************************************************************** */

struct Env_t {
  game g;

};

/* **************************************************************** */

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[]) {
  Env *env = malloc(sizeof(struct Env_t));

  PRINT("> action : help\n");
  PRINT("-press 'w <i> <j>' to put a zero/white at square (i,j)\n");
  PRINT("-press 'b <i> <j>' to put a one/black at square (i,j)\n");
  PRINT("-press 'e <i> <j>' to empty square (i,j)\n");
  PRINT("-press 's <filename>' to save current grid in a file filename.txt\n");
  PRINT("-press 'r' to restart \n");
  PRINT("-press 'q' to quit \n");
  PRINT("-press 'z' to undo\n");
  PRINT("-press 'y' to redo\n");
  return env;
}

/* **************************************************************** */

void render(SDL_Window *win, SDL_Renderer *ren, Env *env) { /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
}

/* **************************************************************** */

bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e) {
  if (e->type == SDL_QUIT) {
    return true;
  }

  /* PUT YOUR CODE HERE TO PROCESS EVENTS */

  return false;
}

/* **************************************************************** */

void clean(SDL_Window *win, SDL_Renderer *ren, Env *env) {
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */

  free(env);
}

/* **************************************************************** */