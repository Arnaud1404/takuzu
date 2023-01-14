#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_struct.h"

game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping, bool unique)
{
  game g = (game)malloc(sizeof(game));
  square* tableau = malloc(sizeof(square) * nb_cols * nb_rows);
  if (g == NULL || tableau == NULL) {
    free(g);
    free(tableau);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < nb_cols * nb_rows; i++) {
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
    free(tableau);
    queue_free(t);
    queue_free(s);
    exit(EXIT_FAILURE);
  }
  g->to_undo = s;
  g->to_redo = t;
  return g;
}

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
  return g;
}

uint game_nb_rows(cgame g) { return g->row; }

uint game_nb_cols(cgame g) { return g->col; }

bool game_is_wrapping(cgame g) { return g->wrap; }

bool game_is_unique(cgame g) { return g->uni; }

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
  square old = game_get_square(g,move->i,move->j);
  game_set_square(g, move->i, move->j, move->s);
  move->s = old;
  queue_push_head(g->to_redo,move);
}

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
  square old = game_get_square(g,move->i,move->j);
  game_set_square(g, move->i, move->j, move->s);
  move->s = old;
  queue_push_head(g->to_undo, move);
}