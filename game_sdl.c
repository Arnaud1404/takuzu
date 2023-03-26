// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include "game_sdl.h"

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"

/* **************************************************************** */
#define NOIR "noir.png"
#define BLANC "blanc.png"
#define IMMUB "immu_blanc.png"
#define IMMUN "immu_noir.png"
#define FONT "SpaceCrusaders.ttf"
#define FAIL "erreur.png"
#define FONTSIZE 20

/* **************************************************************** */

struct Env_t {
  game g;
  int col;
  int lign;
  SDL_Texture* text;
  SDL_Texture* win;
  SDL_Texture* noir;
  SDL_Texture* blanc;
  SDL_Texture* immu_b;
  SDL_Texture* immu_n;
  SDL_Texture* erreur;
};

/* **************************************************************** */

Env* init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[])
{
  Env* env = malloc(sizeof(struct Env_t));
  if (argc == 2) {
    char* filename = argv[1];
    env->g = game_load(filename);
  } else {
    env->g = game_default();
  }
  env->noir = IMG_LoadTexture(ren, NOIR);
  env->blanc = IMG_LoadTexture(ren, BLANC);
  env->immu_b = IMG_LoadTexture(ren, IMMUB);
  env->immu_n = IMG_LoadTexture(ren, IMMUN);
  env->erreur = IMG_LoadTexture(ren, FAIL);
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

  SDL_Color color = {0, 55, 80, 92}; /* blue color in RGBA */
  SDL_Color red = {0, 255, 0, 0};
  TTF_Font* font = TTF_OpenFont(FONT, FONTSIZE);
  TTF_Font* font1 = TTF_OpenFont(FONT, 36);
  SDL_Surface* surf = TTF_RenderText_Blended(font, "press [h] to get help :)", color);
  SDL_Surface* surf1 = TTF_RenderText_Blended(font1, "WINNER", red);
  env->text = SDL_CreateTextureFromSurface(ren, surf);
  env->win = SDL_CreateTextureFromSurface(ren, surf1);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);
  SDL_SetWindowSize(win, env->col * 50 + 100, env->lign * 50 + 100);
  return env;
}

/* **************************************************************** */

void render(SDL_Window* win, SDL_Renderer* ren, Env* env)
{ /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
  SDL_Rect rect;
  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
  rect.x = 50;
  rect.y = h - 25;
  SDL_RenderCopy(ren, env->text, NULL, &rect);

  if (game_is_over(env->g)) {
    SDL_QueryTexture(env->win, NULL, NULL, &rect.w, &rect.h);
    rect.x = 50;
    rect.y = 5;
    SDL_RenderCopy(ren, env->win, NULL, &rect);
  }

  SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
  for (int i = 0; i < env->col + 1; i++) {
    SDL_RenderDrawLine(ren, i * 50 + 50, 50, i * 50 + 50, (env->lign) * 50 + 50);
  }
  for (int i = 0; i < env->col + 1; i++) {
    SDL_RenderDrawLine(ren, 50, i * 50 + 50, (env->col) * 50 + 50, i * 50 + 50);
  }
  for (int i = 0; i < env->col; i++) {
    for (int j = 0; j < env->lign; j++) {
      if ((game_has_error(env->g, i, j) != 0)) {
        SDL_QueryTexture(env->erreur, NULL, NULL, &rect.w, &rect.h);
        rect.x = j * 50 + 50;
        rect.y = i * 50 + 50;
        SDL_RenderCopy(ren, env->erreur, NULL, &rect);
      }
      int s = game_get_number(env->g, i, j);
      if (s == 1) {
        if (game_is_immutable(env->g, i, j)) {
          SDL_QueryTexture(env->immu_n, NULL, NULL, &rect.w, &rect.h);
          rect.x = j * 50 + 50;
          rect.y = i * 50 + 50;
          SDL_RenderCopy(ren, env->immu_n, NULL, &rect);
        } else {
          SDL_QueryTexture(env->noir, NULL, NULL, &rect.w, &rect.h);
          rect.x = j * 50 + 50;
          rect.y = i * 50 + 50;
          SDL_RenderCopy(ren, env->noir, NULL, &rect);
        }
      } else if (s == 0) {
        if (game_is_immutable(env->g, i, j)) {
          SDL_QueryTexture(env->immu_b, NULL, NULL, &rect.w, &rect.h);
          rect.x = j * 50 + 50;
          rect.y = i * 50 + 50;
          SDL_RenderCopy(ren, env->immu_b, NULL, &rect);
        } else {
          SDL_QueryTexture(env->blanc, NULL, NULL, &rect.w, &rect.h);
          rect.x = j * 50 + 50;
          rect.y = i * 50 + 50;
          SDL_RenderCopy(ren, env->blanc, NULL, &rect);
        }
      }
    }
  }
}

/* **************************************************************** */

bool process(SDL_Window* win, SDL_Renderer* ren, Env* env, SDL_Event* e)
{
  if (e->type == SDL_QUIT) {
    return true;
  } else if (e->type == SDL_MOUSEBUTTONDOWN) {
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    int x = mouse.x / 50 - 1;
    int y = mouse.y / 50 - 1;
    int vider = game_get_number(env->g, y, x);
    if (vider == -1) {
      if (e->button.button == SDL_BUTTON_LEFT) {
        game_play_move(env->g, y, x, S_ONE);
      } else
        (game_play_move(env->g, y, x, S_ZERO));
    } else
      (game_play_move(env->g, y, x, S_EMPTY));
  } else if (e->type == SDL_KEYDOWN) {
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

void clean(SDL_Window* win, SDL_Renderer* ren, Env* env)
{
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */
  SDL_DestroyTexture(env->text);
  SDL_DestroyTexture(env->win);
  SDL_DestroyTexture(env->noir);
  SDL_DestroyTexture(env->blanc);
  SDL_DestroyTexture(env->immu_b);
  SDL_DestroyTexture(env->immu_n);
  SDL_DestroyTexture(env->erreur);
  free(env);
}

/* **************************************************************** */
