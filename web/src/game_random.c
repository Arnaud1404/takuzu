/**
 * @file game_random.c
 * @copyright University of Bordeaux. All rights reserved, 2022.
 **/

#include "game_random.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"

/* ************************************************************************** */
/*                            Random Game Generator                           */
/* ************************************************************************** */

static game game_set_some_mutable_squares(game g, uint nb_empty)
{
  assert(g);
  uint nb_rows = game_nb_rows(g);
  uint nb_cols = game_nb_cols(g);
  uint nb_squares = nb_rows * nb_cols;
  assert(nb_empty <= nb_squares);
  uint nb_empty1 = nb_empty;
  while (nb_empty1 > 0) {
    uint pos = rand() % nb_squares;
    uint row = pos / nb_cols;
    uint col = pos % nb_cols;
    if (game_is_immutable(g, row, col)) {
      square s = game_get_number(g, row, col);
      game_set_square(g, row, col, s + 1);
      nb_empty1--;
    }
  }
  return g;
}

/* ************************************************************************** */

static void game_flip_one_square(game g, int i, int j)
{
  square s = game_get_square(g, i, j);
  if (s == S_IMMUTABLE_ONE)
    game_set_square(g, i, j, S_IMMUTABLE_ZERO);
  else
    game_set_square(g, i, j, S_IMMUTABLE_ONE);
}

/* ************************************************************************** */

static bool try_flip(game g, int i1, int j1, int i2, int j2)
{
  if (i1 == i2 && j1 == j2) return false;
  assert(game_is_over(g));
  square s11 = game_get_square(g, i1, j1);
  square s22 = game_get_square(g, i2, j2);
  square s12 = game_get_square(g, i1, j2);
  square s21 = game_get_square(g, i2, j1);

  if (s11 == s22 && s12 == s21 && s11 != s12) {
    game_flip_one_square(g, i1, j1);
    game_flip_one_square(g, i2, j2);
    game_flip_one_square(g, i1, j2);
    game_flip_one_square(g, i2, j1);

    if (game_is_over(g)) {
      return true;
    } else {  // undo
      game_flip_one_square(g, i1, j1);
      game_flip_one_square(g, i2, j2);
      game_flip_one_square(g, i1, j2);
      game_flip_one_square(g, i2, j1);
      assert(game_is_over(g));
      return false;
    }
  }
  return false;
}

/* ************************************************************************** */

static void apply_nb_flips(game g, uint nb)
{
  uint nb_rows = game_nb_rows(g);
  uint nb_cols = game_nb_cols(g);
  while (nb > 0) {
    uint i1 = rand() % nb_rows;
    uint j1 = rand() % nb_cols;
    uint i2 = rand() % nb_rows;
    uint j2 = rand() % nb_cols;
    if (try_flip(g, i1, j1, i2, j2)) nb--;
  }
}

/* ************************************************************************** */

game game_random(uint nb_rows, uint nb_cols, bool wrapping, uint uniq, bool with_solution)
{
  // step 0: create an empty game
  game g = game_new_empty_ext(nb_rows, nb_cols, wrapping, uniq);

  // fill the grid with initial values
  for (uint i = 0; i < nb_rows; i++)
    for (uint j = 0; j < nb_cols; j++) game_set_square(g, i, j, (i + j) % 2 + 3);

  // Make it unique if it is square
  if (nb_cols == nb_rows) {
    for (uint i = 0; i < nb_rows / 2; i++) {
      game_flip_one_square(g, 2 * i, 2 * i);
      game_flip_one_square(g, 2 * i, 2 * i + 1);
      game_flip_one_square(g, 2 * i + 1, 2 * i);
      game_flip_one_square(g, 2 * i + 1, 2 * i + 1);
    }
  }
  assert(game_is_over(g));
  // apply some flips
  apply_nb_flips(g, nb_rows * nb_cols * 10);

  assert(game_is_over(g));
  // check

  game_set_some_mutable_squares(g, (nb_rows * nb_cols * 1) / 2);
  if (!with_solution) game_restart(g);
  return g;
}

/* ************************************************************************** */