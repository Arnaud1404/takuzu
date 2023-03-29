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
#define NOIR "./resources/images/noir.png"
#define BLANC "./resources/images/blanc.png"
#define IMMUB "./resources/images/immu_blanc.png"
#define IMMUN "./resources/images/immu_noir.png"
#define FONT "./resources/fonts/Bubblegum.ttf"
#define FAIL "./resources/images/erreur.png"
#define BSOLVE "./resources/images/solve.png"
#define BQUIT "./resources/images/Quit.png"
#define BREDO "./resources/images/redo.png"
#define BUNDO "./resources/images/undo.png"
#define BSAVE "./resources/images/save.png"
#define BRESTART "./resources/images/restart.png"

#define S_PIXEL 50
#define FONTSIZE 20

/* **************************************************************** */

//initialisation de l'environnement
struct Env_t { 
  game g;
  int col;
  int lign;
  int ctrl;
  const char* help_text;
  const char* help_title;
  const char* no_sol_title;
  const char* no_sol_text;
  const char* save_title;
  const char* save_text;
  char* save;
  SDL_Texture* b_restart;
  SDL_Texture* b_solve;
  SDL_Texture* b_undo;
  SDL_Texture* b_save;
  SDL_Texture* b_quit;
  SDL_Texture* b_redo;
  SDL_Texture* text;
  SDL_Texture* title;
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
    env->g = game_default(); //charge le jeu par défaut si aucun jeu n'est donné en paramètre
  }
  env->col = game_nb_cols(env->g);
  env->lign = game_nb_rows(env->g);
  env->ctrl = 0;
  //chargement des sprites

  env->noir = IMG_LoadTexture(ren, NOIR);
  env->blanc = IMG_LoadTexture(ren, BLANC);
  env->immu_b = IMG_LoadTexture(ren, IMMUB);
  env->immu_n = IMG_LoadTexture(ren, IMMUN);
  env->erreur = IMG_LoadTexture(ren, FAIL);


  env->b_restart = IMG_LoadTexture(ren, BRESTART);
  env->b_solve = IMG_LoadTexture(ren, BSOLVE);
  env->b_undo = IMG_LoadTexture(ren, BUNDO);
  env->b_save = IMG_LoadTexture(ren, BSAVE);
  env->b_quit = IMG_LoadTexture(ren, BQUIT);
  env->b_redo = IMG_LoadTexture(ren, BREDO);

  //initialisation des textes pour les messagebox
  env->help_text =
      "-click on an empty square to play white\n"
      "-click on a white square to play black\n"
      "-click on a black square to empty it\n"
      "-press 'r' to restart \n"
      "-press 'q' to quit \n"
      "-press 'z' to undo\n"
      "-press 'y' to redo\n"
      "-press 's' to search the solution of the game\n"
      "-press 'ctrl'+'s' to save";
  env->help_title = "Help";
  env->no_sol_title = "Oops";
  env->no_sol_text = "No existing solution for this game!\n";
  env->save = "save.txt";
  env->save_title = "Sauvegarde";
  env->save_text = "Sauvegarde bien effectuée dans le dossier du jeu";
  SDL_SetWindowSize(win, SCREEN_WIDTH+2*S_PIXEL, SCREEN_HEIGHT);

  SDL_Color pink = {255, 105, 180, 0}; //rose

  TTF_Font* font = TTF_OpenFont(FONT, FONTSIZE);
  TTF_Font* font1 = TTF_OpenFont(FONT, 50);
  SDL_Surface* surf = TTF_RenderText_Blended(font, "press [h] to get help :)", pink);
  SDL_Surface* surf1 = TTF_RenderText_Blended(font1, "WINNER", pink);
  SDL_Surface* surf2 = TTF_RenderText_Blended(font, "TAKUZU", pink);
  env->text = SDL_CreateTextureFromSurface(ren, surf);
  env->win = SDL_CreateTextureFromSurface(ren, surf1);
  env->title = SDL_CreateTextureFromSurface(ren, surf2);

  //libère les espaces
  SDL_FreeSurface(surf);
  SDL_FreeSurface(surf1);
  TTF_CloseFont(font);
  TTF_CloseFont(font1);
  
  return env;
}

/* **************************************************************** */

void render(SDL_Window* win, SDL_Renderer* ren, Env* env)
{ 

  SDL_Rect rect;
  int w, h;
  SDL_GetWindowSize(win, &w, &h); 
  //on compare la taille de la fenêtre à la taille originale
  float ratiow = w/((float)env->col * S_PIXEL +S_PIXEL*2 );
  float ratioh = h/((float)env->lign * S_PIXEL + S_PIXEL*2);
  float ratio;
  if(ratiow<ratioh){ 
    ratio = ratiow;  
  }
  else{
    ratio = ratioh;
  }
  
  float size = S_PIXEL*ratio; //redimensionne la taille d'une case
  
  SDL_QueryTexture(env->b_restart, NULL, NULL, &rect.w, &rect.h);
  rect.x = 5*ratio;
  rect.y = size+5*ratio;
  rect.w = rect.w*ratio-size;
  rect.h = rect.h*ratio;
  SDL_RenderCopy(ren, env->b_restart, NULL, &rect);

  SDL_QueryTexture(env->b_solve, NULL, NULL, &rect.w, &rect.h);
  rect.x = 5*ratio;
  rect.y = size*2+10*ratio;
  rect.w = rect.w*ratio-size;
  rect.h = rect.h*ratio;
  SDL_RenderCopy(ren, env->b_solve, NULL, &rect);

  SDL_QueryTexture(env->b_undo, NULL, NULL, &rect.w, &rect.h);
  rect.x = 5*ratio;
  rect.y = size*3+10*ratio;
  rect.w = rect.w*ratio-size;
  rect.h = rect.h*ratio;
  SDL_RenderCopy(ren, env->b_undo, NULL, &rect);

  SDL_QueryTexture(env->b_save, NULL, NULL, &rect.w, &rect.h);
  rect.x = (env->col * size) + w/2.0+(env->col/2)*size + 10*ratio;
  rect.y = size+5*ratio;
  rect.w = rect.w*ratio-size;
  rect.h = rect.h*ratio;
  SDL_RenderCopy(ren, env->b_save, NULL, &rect);

  SDL_QueryTexture(env->b_quit, NULL, NULL, &rect.w, &rect.h);
  rect.x = (env->col * size) + w/2.0+(env->col/2)*size + 10*ratio;
  rect.y = size*2+10*ratio;
  rect.w = rect.w*ratio;
  rect.h = rect.h*ratio;
  SDL_RenderCopy(ren, env->b_quit, NULL, &rect);

  SDL_QueryTexture(env->b_redo, NULL, NULL, &rect.w, &rect.h);
  rect.x = (env->col * size) + w/2.0+(env->col/2)*size + 10*ratio;
  rect.y = size*3+10*ratio;
  rect.w = rect.w*ratio;
  rect.h = rect.h*ratio;
  SDL_RenderCopy(ren, env->b_redo, NULL, &rect);

  SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/4;
  rect.y = h-size/2;
  rect.w = rect.w*ratio;
  rect.h = rect.h*ratio;
  SDL_RenderCopy(ren, env->text, NULL, &rect); //placement du texte d'indication pour help

  if(!game_is_over(env->g)){ //sinon conflit avec texte winner
  SDL_QueryTexture(env->title, NULL, NULL, &rect.w, &rect.h);
    rect.x = w/2-size;
    rect.y = h/100;
    rect.w = rect.w * ratio;
    rect.h = rect.h*ratio;
    SDL_RenderCopy(ren, env->title, NULL, &rect); //placement du texte "takuzu"
  }

  //traçage de la grille 
  SDL_SetRenderDrawColor(ren, 255, 105, 180, SDL_ALPHA_OPAQUE); //noir
  for (int i = 0; i < env->col + 1; i++) {
    SDL_RenderDrawLine(ren, (i * size) + w/2.0-(env->col/2)*size, (h/2-env->lign/2*size) , (i * size + w/2-env->col/2*size), ((env->lign) * size + h/2-env->lign/2*size));
  }
  for (int i = 0; i < env->lign + 1; i++) {
    SDL_RenderDrawLine(ren, (w/2-env->col/2*size), (i * size + h/2-env->lign/2*size), ((env->col) * size + w/2-env->col/2*size), (i * size + h/2-env->lign/2*size));
  }

  //affichage du contenu des cases
  for (int i = 0; i < env->lign; i++) {
    for (int j = 0; j < env->col; j++) {
      if ((game_has_error(env->g, i, j) != 0)) {
        SDL_QueryTexture(env->erreur, NULL, NULL, &rect.w, &rect.h);
        rect.x = (j * size + w/2-(env->col/2)*size);
        rect.y = (i * size + h/2-env->lign/2*size);
        rect.h = size;
        rect.w = size;
        SDL_RenderCopy(ren, env->erreur, NULL, &rect);
      }
      int s = game_get_number(env->g, i, j);
      if (s == 1) {

        //affiche les cases noires

        if (game_is_immutable(env->g, i, j)) {
          SDL_QueryTexture(env->immu_n, NULL, NULL, &rect.w, &rect.h);
          rect.x = (j * size + w/2-(env->col/2)*size); //position du sprite
          rect.y = (i * size + h/2-env->lign/2*size);
          rect.w = size; //redimensionnement du sprite
          rect.h = size;
          SDL_RenderCopy(ren, env->immu_n, NULL, &rect);
        } else {
          SDL_QueryTexture(env->noir, NULL, NULL, &rect.w, &rect.h);
          rect.x = (j * size + w/2-(env->col/2)*size);
          rect.y = (i * size + h/2-env->lign/2*size);
          rect.w = size;
          rect.h = size;
          SDL_RenderCopy(ren, env->noir, NULL, &rect);
        }
      } else if (s == 0) {

        //affiche les cases blanches

        if (game_is_immutable(env->g, i, j)) {
          SDL_QueryTexture(env->immu_b, NULL, NULL, &rect.w, &rect.h);
          rect.x = (j * size + w/2-(env->col/2)*size);
          rect.y = (i * size + h/2-env->lign/2*size);
          rect.w = size;
          rect.h = size;
          SDL_RenderCopy(ren, env->immu_b, NULL, &rect);
        } else {
          SDL_QueryTexture(env->blanc, NULL, NULL, &rect.w, &rect.h);
          rect.x = (j * size + w/2-(env->col/2)*size);
          rect.y = (i * size + h/2-env->lign/2*size);
          rect.w = size;
          rect.h = size;
          SDL_RenderCopy(ren, env->blanc, NULL, &rect);
        }
      }
    }
  }
  //si le jeu est gagné, écrit winner sur la fenêtre
  if (game_is_over(env->g)) {
    SDL_QueryTexture(env->win, NULL, NULL, &rect.w, &rect.h);
    rect.x = w/3;
    rect.y = 0;
    rect.w = rect.w * ratio;
    rect.h = rect.h*ratio;
    SDL_RenderCopy(ren, env->win, NULL, &rect);
  }

}

/* **************************************************************** */
bool process(SDL_Window* win, SDL_Renderer* ren, Env* env, SDL_Event* e)
{ 

  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  float ratiow = w/((float)env->col * S_PIXEL + 4*S_PIXEL);
  float ratioh = h/((float)env->lign * S_PIXEL + 2*S_PIXEL);
  float ratio;
  if(ratiow<ratioh){
    ratio = ratiow;  
  }
  else{
    ratio = ratioh;
  } 
  float size = S_PIXEL*ratio;


  if (e->type == SDL_QUIT) {
    return true;
  } else if (e->type == SDL_MOUSEBUTTONDOWN) {

    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    int x = (mouse.x-(w/2-env->col/2*size)) /size;
    int y = (mouse.y-(h/2-env->lign/2*size))/size;

    if((mouse.x <= (2*size- 5*ratio)) && ( mouse.y >= (size+5*ratio))  &&  (mouse.x >= 5*ratio) && (mouse.y <= size*2+5*ratio)){
      game_restart(env->g);
    }

    if((mouse.x <= (2*size- 5*ratio)) && ( mouse.y >= (size*2+10*ratio))  &&  (mouse.x >= 5*ratio) && (mouse.y <= size*3+5*ratio)){
      game_solve(env->g);
    }

    if((mouse.x <= (2*size- 5*ratio)) && ( mouse.y >= (size*3+10*ratio))  &&  (mouse.x >= 5*ratio) && (mouse.y <= size*4+5*ratio)){
      game_undo(env->g);
    }

    if((mouse.x <= (w-5*ratio)) && ( mouse.y >= (size+5*ratio))  &&  (mouse.x >= w-2*size) && (mouse.y <= size*2+5*ratio)){
      game_save(env->g,env->save);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,env->save_title,env->save_text,win);
    }
    if((mouse.x <= (w-5*ratio)) && ( mouse.y >= (size*2+5*ratio))  &&  (mouse.x >= w-2*size) && (mouse.y <= size*3+5*ratio)){
      return true;
    }
    if((mouse.x <= (w-5*ratio)) && ( mouse.y >= (size*3+5*ratio))  &&  (mouse.x >= w-2*size) && (mouse.y <= size*4+5*ratio)){
      game_redo(env->g);
    }

    //si on clique hors de la grille rien ne se passe
    if(x< env->col && y <env->lign && mouse.x >= 2*size && mouse.y >= size && x>=0 && y >=0){ 

    int carre = game_get_number(env->g, y, x);
    if (carre == -1) { //on ne joue que dans des cases vides
        game_play_move(env->g, y, x, S_ZERO);
    } 
       else if (carre == 0){
        (game_play_move(env->g, y, x, S_ONE));
       }
      else{
      (game_play_move(env->g, y, x, S_EMPTY));
    }
   
  }      
  }
  else{ if (e->type == SDL_KEYUP){
    if((e->key.keysym.sym==SDLK_LCTRL)){
      
      env->ctrl  = 0;
    }
  } 
  if (e->type == SDL_KEYDOWN) {
    if(e->key.keysym.sym == SDLK_LCTRL){
      env->ctrl  = 1;
    }
    switch (e->key.keysym.sym) {
      case SDLK_z:
        game_undo(env->g);
        break;
      case SDLK_y:
        game_redo(env->g);
        break;
      case SDLK_q:
        return true;
      case SDLK_s:
        if(env->ctrl == 1){
          game_save(env->g,env->save);
          SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,env->save_title,env->save_text,win);
        }
        else{
        game_restart(env->g);
        if (!game_solve(env->g)) {
          SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,env->no_sol_title,env->no_sol_text,win); //affiche une erreur si il n'y a pas de solutions au jeu proposé
        }
        }
        break;
      case SDLK_r:
        game_restart(env->g);
        break;
 
      case SDLK_h:

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,env->help_title,env->help_text,win);
        break; 
    }
  }
  }
  return false;
}

/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env* env)
{

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
