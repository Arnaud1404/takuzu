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
  else{
  env->g = game_default();
  }
  PRINT("-press 'w <i> <j>' to put a zero/white at square (i,j)\n");
  PRINT("-press 'b <i> <j>' to put a one/black at square (i,j)\n");
  PRINT("-press 'e <i> <j>' to empty square (i,j)\n");
  PRINT("-press 's <filename>' to save current grid in a file filename.txt\n");
  PRINT("-press 'r' to restart \n");
  PRINT("-press 'q' to quit \n");
  PRINT("-press 'z' to undo\n");
  PRINT("-press 'y' to redo\n");
  PRINT("-press 's' to search the solution of the game\n");
  PRINT("-press 'c' to count the number of solution and save it\n");
  env->col = game_nb_cols(env->g);
  env->lign = game_nb_rows(env->g);
  SDL_SetWindowSize(win, env->col*50+100,
                       env->lign*50+100);
  return env;
}

/* **************************************************************** */

void render(SDL_Window *win, SDL_Renderer *ren, Env *env) { /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
for(int i = 0; i < env->col +1;i++){
  SDL_RenderDrawLine(ren,i*50+50, 50,i*50+50 ,(env->lign)*50+50);
}
for(int i = 0; i < env->col +1;i++){
  SDL_RenderDrawLine(ren,50,i*50+50,(env->col)*50+50,i*50+50);
}
for(int i = 0; i < env->col ;i++){
  for(int j = 0; j < env->lign ;j++){
    if ((game_has_error(env->g, i, j) != 0)) {
          PRINT("Error at square(%d,%d)\n", i, j);
        }
    int s = game_get_number(env->g,i,j);
    if(s == 0){
    SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
    const float pi = 3.14159265358979323846264338327950288419716939937510;
    float step = 2 * pi / 300; /* smoothing */
    for (float theta = 0.0; theta <= 2 * pi; theta += step) {
    int x1 = j*50+25+50 +  25*cosf(theta) + 0.5;
    int y1 = i*50+25+50 + 25*sinf(theta) + 0.5;
    SDL_RenderDrawPoint(ren, x1, y1);
    }    
    }
    else if(s == 1){
    SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
    const float pi = 3.14159265358979323846264338327950288419716939937510;
    float step = 2 * pi / 300; /* smoothing */
    for (float theta = 0.0; theta <= 2 * pi; theta += step) {
    int x1 = j*50+25+50 +  25*cosf(theta) + 0.5;
    int y1 = i*50+25+50 + 25*sinf(theta) + 0.5;
    SDL_RenderDrawPoint(ren, x1, y1);
    }      
    }
  }
}
}

/* **************************************************************** */

bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e) {
  if (e->type == SDL_QUIT) {
    return true;
  }
  else if (e->type == SDL_MOUSEBUTTONDOWN){
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x,&mouse.y);
    int x = mouse.x/50-1;
    int y = mouse.y/50-1;
    int vider = game_get_number(env->g,y,x);
    if(vider == -1){
    if(e->button.button == SDL_BUTTON_LEFT){
    game_play_move(env->g,y,x,S_ONE);
    }
    else(game_play_move(env->g,y,x,S_ZERO));
    }
    else(game_play_move(env->g,y,x,S_EMPTY));
  }
  else if (e->type == SDL_KEYDOWN) {
    switch (e->key.keysym.sym) {
      case SDLK_y:
        game_undo(env->g);
        break;
      case SDLK_z:
        game_redo(env->g);
        break;  
      case SDLK_q:
        return true;
      case SDLK_s:
        game_solve(env->g);
      case SDLK_c:
        game_nb_solutions(env->g);
      case SDLK_r:
        game_restart(env->g);             
    }
  }
  return false;
}

/* **************************************************************** */

void clean(SDL_Window *win, SDL_Renderer *ren, Env *env) {
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */

  free(env);
}

/* **************************************************************** */
