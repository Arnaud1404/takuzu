// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include "game_sdl.h"
#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"
#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* **************************************************************** */
#define NOIR "noir.png"
#define BLANC "blanc.png"

/* **************************************************************** */

struct Env_t {
  game g;
  int col;
  int lign;

};

/* **************************************************************** */

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[]) {
  Env *env = malloc(sizeof(struct Env_t));
  if(argc == 2){
    char* filename = argv[1];
    env->g = game_load(filename);
  }
  env->g = game_default();
  PRINT("> action : help\n");
  PRINT("-press 'w <i> <j>' to put a zero/white at square (i,j)\n");
  PRINT("-press 'b <i> <j>' to put a one/black at square (i,j)\n");
  PRINT("-press 'e <i> <j>' to empty square (i,j)\n");
  PRINT("-press 's <filename>' to save current grid in a file filename.txt\n");
  PRINT("-press 'r' to restart \n");
  PRINT("-press 'q' to quit \n");
  PRINT("-press 'z' to undo\n");
  PRINT("-press 'y' to redo\n");
  env->col = game_nb_cols(env->g);
  env->lign = game_nb_rows(env->g);
  return env;
}

/* **************************************************************** */

void render(SDL_Window *win, SDL_Renderer *ren, Env *env) { /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
for(int i = 0; i < env->col +1;i++){
  SDL_RenderDrawLine(ren,i*50, 0,i*50 ,(env->lign)*50);
}
for(int i = 0; i < env->col +1;i++){
  SDL_RenderDrawLine(ren,0,i*50,(env->col)*50,i*50);
}
for(int i = 0; i < env->col +1;i++){
  for(int j = 0; j < env->lign +1;j++){
    square s = game_get_square(env->g,i,j);
    if(s == 0){
    SDL_SetRenderDrawColor(ren, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_Texture* noir = IMG_LoadTexture(ren, NOIR);
    SDL_RenderDrawLine(ren, i*50 , j*50,i*50+20,j*50+20);      
    }
    else if(s ==1){
    SDL_SetRenderDrawColor(ren, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(ren, i*50 , j*50,i*50+20,j*50+20);     
    }
  }
}
}

/* **************************************************************** */

bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e) {
  if (e->type == SDL_QUIT) {
    return true;
  }


  return false;
}

/* **************************************************************** */

void clean(SDL_Window *win, SDL_Renderer *ren, Env *env) {
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */

  free(env);
}

/* **************************************************************** */
