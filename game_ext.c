#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_struct.h"
#include "queue.h"

// crée et renvoie un jeu avec des paramètres spécifiques entrés en paramètre
// avec nb_rows le nombre voulu de colonne, nb_cols le nombre de colonnes
// un bool pour choisir si le jeu se replie sur lui même (wrap)
// un bool pour choisir si il est possible d'avoir deux lignes/colonnes identiques dans le jeu
game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping, bool unique)
{
  game g = (game)malloc(sizeof(struct game_s));
  if (g == NULL || squares == NULL) {
    free(g);
    exit(EXIT_FAILURE);
  }
  square* tableau = malloc(sizeof(square) * nb_rows * nb_cols);
  if (tableau == NULL) {
    free(g);
    free(tableau);
    exit(EXIT_FAILURE);
  }
  for (uint i = 0; i < nb_rows * nb_cols; i++) {
    tableau[i] = squares[i];
  }
  g->tab = tableau;
  g->col = nb_cols;
  g->row = nb_rows;
  g->uni = unique;
  g->wrap = wrapping;
  queue* s = queue_new();
  queue* t = queue_new();
  if (s == NULL || t == NULL) {
    free(g);
    free(squares);
    queue_free_full(t, free);
    queue_free_full(s, free);
    exit(EXIT_FAILURE);
  }
  g->to_undo = s;
  g->to_redo = t;
  return g;
}

// crée un nouveau jeu vide avec les paramètre de la v2
game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping, bool unique)
{
  square* tableau = malloc(sizeof(square) * nb_cols * nb_rows);
  if (tableau == NULL) {
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < nb_cols * nb_rows; i++) {
    tableau[i] = S_EMPTY;
  }
  game g = game_new_ext(nb_rows, nb_cols, tableau, wrapping, unique);
  free(tableau);
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
  square new = game_get_square(g, move->i, move->j);
  game_set_square(g, move->i, move->j, move->s);
  move->s = new;
  queue_push_head(g->to_redo, move);
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
  square new = game_get_square(g, move->i, move->j);
  game_set_square(g, move->i, move->j, move->s);
  move->s = new;
  queue_push_head(g->to_undo, move);
}