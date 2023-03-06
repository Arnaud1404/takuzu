/**
 * @file game_tools.h
 * @brief Game Tools.
 * @details See @ref index for further details.
 * @copyright University of Bordeaux. All rights reserved, 2022.
 *
 **/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_ext.h"
/**
 * @name Game Tools
 * @{
 */

/**
 * @brief Creates a game by loading its description from a text file.
 * @details See the file format description in @ref index.
 * @param filename input file
 * @return the loaded game
 **/
game game_load(char* filename)
{
  if (filename == NULL) {
    exit(EXIT_FAILURE);
  }
  FILE* file_game = fopen(filename, "r");
  if (file_game == NULL) {
    exit(EXIT_FAILURE);
  }
  int col;
  int lin;
  int wra;
  int uni;
  int a = fscanf(file_game, "%d %d %d %d", &lin, &col, &wra, &uni);
  if (a != 4) {
    exit(EXIT_FAILURE);
  }
  char tab[lin * col];
  char tmp;
  for (int i = 0; i < col * lin; i++) {
    tmp = fgetc(file_game);
    if (tmp == '\n') {
      tmp = fgetc(file_game);
    }
    tab[i] = tmp;
  }

  square tab_sq[lin * col];
  for (int i = 0; i < col * lin; i++) {
    switch (tab[i]) {
      case 'e':
        tab_sq[i] = S_EMPTY;
        break;
      case 'w':
        tab_sq[i] = S_ZERO;
        break;
      case 'b':
        tab_sq[i] = S_ONE;
        break;
      case 'W':
        tab_sq[i] = S_IMMUTABLE_ZERO;
        break;
      case 'B':
        tab_sq[i] = S_IMMUTABLE_ONE;
        break;
    }
  }
  game new_game = game_new_ext(lin, col, tab_sq, wra, uni);
  fclose(file_game);
  return new_game;
}

/**
 * @brief Saves a game in a text file.
 * @details See the file format description in @ref index.
 * @param g game to save
 * @param filename output file
 **/
void game_save(cgame g, char* filename)
{
  if (filename == NULL) {
    exit(EXIT_FAILURE);
  }
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  FILE* file_game = fopen(filename, "w");
  if (file_game == NULL) {
    exit(EXIT_FAILURE);
  }

  int nb_rows = game_nb_rows(g);
  int nb_cols = game_nb_cols(g);
  int wrap = game_is_wrapping(g);
  int uni = game_is_unique(g);

  fprintf(file_game, "%d %d %d %d\n", nb_rows, nb_cols, wrap, uni);

  for (int i = 0; i < nb_rows; i++) {
    for (int j = 0; j < nb_cols; j++) {
      switch (game_get_square(g, i, j)) {
        case S_EMPTY:
          fprintf(file_game, "e");
          break;
        case S_ZERO:
          fprintf(file_game, "w");
          break;
        case S_ONE:
          fprintf(file_game, "b");
          break;
        case S_IMMUTABLE_ZERO:
          fprintf(file_game, "W");
          break;
        case S_IMMUTABLE_ONE:
          fprintf(file_game, "B");
          break;
      }
    }
    fprintf(file_game, "\n");
  }
  fclose(file_game);
};

bool game_solve(game g){
  game g1 = game_copy(g);
  int nb = 0;
  game_solve_rec(g1,0,&nb);
  if (nb != 0){
    return true;
  }
  return false;
}

void game_solve_rec(game g, uint pos, uint* count )
{
 int nb_cols = game_nb_cols(g);

 if (pos == (nb_cols)*game_nb_rows(g)) { //Condition d'arret (on est arrivé à la dernière case)

 //Ici pas besoin de vérifier que le jeu est terminé avec game_is_over puisque on utilise game_has_error à chaque itération.
 //Et donc on ne peut arriver à la dernière case avec une erreur ou une case vide.
 (*count)++; //On incrémente le nombre de solution (puisque le jeu est finis)

 return;
 }

 uint pos_i=pos / nb_cols, pos_j=pos % nb_cols;

 if (game_get_square(g, pos_i, pos_j) == S_EMPTY) { //Si la case actuelle est vide alors on essaie 

 game_set_square(g, pos_i, pos_j, S_ZERO); //On joue S_ZERO 
 if (game_has_error(g,pos_i,pos_j)==0){ //Si ce coup n'a pas provoqué d'erreur dans le jeu alors on continue les appels sinon on essaie autre chose
 game_solve_rec(g, pos + 1, count);
 }

 game_set_square(g, pos_i, pos_j, S_ONE); //On joue S_ONE

 if (game_has_error(g,pos_i,pos_j)==0){ //Si ce coup n'a pas provoqué d'erreur dans le jeu alors on continue les appels sinon one ne fait rien (et donc on retourne en arrière)
 game_solve_rec(g, pos + 1, count);
 }

 game_set_square(g, pos_i, pos_j, S_EMPTY); //Après les éventuels appels on remets la case à S_ZERO (pour les précedents appels en attente)

 //Ici plus rien ne se passe donc c'est la fin de l'appel précedent qui s'execute 

 } else {
 game_solve_rec(g, pos + 1, count); //Si le case n'est pas vide alors il suffit de passer à la case suivante
 }
}


uint game_nb_solutions(cgame g){
  return 1;
  
}
