#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_struct.h"

// crée et renvoie un jeu avec des paramètres spécifiques entrés en paramètre
// avec nb_rows le nombre voulu de colonne, nb_cols le nombre de colonnes
// un bool pour choisir si le jeu se replie sur lui même (wrap)
// un bool pour choisir si il est possible d'avoir deux lignes/colonnes identiques dans le jeu
game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping, bool unique)
{
  game g = (game)malloc(sizeof(game));
  square* tableau = malloc(sizeof(square) * nb_rows * nb_cols);
  if (g == NULL || tableau == NULL) {
    free(g);
    free(tableau);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
    tableau[i] = squares[i];
  }
  g->row = nb_rows;
  g->col = nb_cols;
  g->wrap = wrapping;
  g->uni = unique;
  g->tab = tableau;
  queue* s = queue_new();
  queue* t = queue_new();
  if (s == NULL || t == NULL) {
    free(g);
    free(tableau);
    free(s);
    free(t);
    exit(EXIT_FAILURE);
  }
  g->to_redo = s;
  g->to_undo = t;
  return g;
}

// crée un nouveau jeu vide avec les paramètre de la v2
game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping, bool unique)
{
  game g = (game)malloc(sizeof(game));
  square* tableau = malloc(sizeof(square) * nb_rows * nb_cols);
  if (g == NULL || tableau == NULL) {
    free(g);
    free(tableau);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
    tableau[i] = S_EMPTY;
  }
  g->row = nb_rows;
  g->col = nb_cols;
  g->wrap = wrapping;
  g->uni = unique;
  queue* s = queue_new();
  queue* t = queue_new();
  if (s == NULL || t == NULL) {
    free(g);
    free(tableau);
    free(s);
    free(t);
    exit(EXIT_FAILURE);
  }
  g->to_redo = s;
  g->to_undo = t;
  return g;
}

// retourne le nombre de lignes du jeu passé en paramètre
uint game_nb_rows(cgame g) { return g->row; }

// retourne le nombre de colonnes du jeu passé en paramètre
uint game_nb_cols(cgame g) { return g->col; }

// retourne si le jeu peux se replier sur lui-même
bool game_is_wrapping(cgame g) { return g->wrap; }

// retourne si il est possible d'avoir deux lignes/colonnes identiques dans le jeu
bool game_is_unique(cgame g) { return g->uni; }

// défait le dernier coup joué
void game_undo(game g)
{
  if (g->to_undo == NULL) {
    fprintf(stderr, "memory error\n");
    exit(EXIT_FAILURE);
  }
  if (queue_is_empty(g->to_undo)) {
    return;
  }

  move_t* move = queue_pop_head(g->to_undo);
  queue_push_head(g->to_redo, move);
  game_set_square(g, move->i, move->j, move->s);
}

// refait le dernier coup défait
void game_redo(game g)
{
  if (g->to_redo == NULL) {
    fprintf(stderr, "memory error\n");
    exit(EXIT_FAILURE);
  }
  if (queue_is_empty(g->to_redo)) {
    return;
  }
  move_t* move = queue_pop_head(g->to_redo);
  game_set_square(g, move->i, move->j, move->s);
  queue_push_head(g->to_undo, move);
}