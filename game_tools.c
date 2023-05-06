/**
 * @file game_tools.h
 * @brief Game Tools.
 * @details See @ref index for further details.
 * @copyright University of Bordeaux. All rights reserved, 2022.
 *
 **/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
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

static void game_solve_rec(game g, uint pos, uint* count, bool first)
{
  int nb_cols = game_nb_cols(g);

  if (pos == nb_cols * game_nb_rows(g)) {
    (*count)++;
    if (game_is_over(g)) {
      if (first) return;
    }
    return;
  }

  uint posrow = pos / nb_cols;
  uint poscol = pos % nb_cols;

  if (game_get_square(g, posrow, poscol) != S_EMPTY) {
    game_solve_rec(g, pos + 1, count, first);
    return;
  }

  game_set_square(g, posrow, poscol, S_ZERO);
  if (game_has_error(g, posrow, poscol) == 0) {
    game_solve_rec(g, pos + 1, count, first);
    if (first && (*count == 1)) {
      return;
    }
  }

  game_set_square(g, posrow, poscol, S_ONE);
  if (game_has_error(g, posrow, poscol) == 0) {
    game_solve_rec(g, pos + 1, count, first);
    if (first && (*count == 1)) {
      return;
    }
  }
  game_set_square(g, posrow, poscol, S_EMPTY);
}

uint game_nb_solutions(cgame g)
{
  game g1 = game_copy(g);
  uint nb = 0;
  game_solve_rec(g1, 0, &nb, false);
  game_delete(g1);
  return nb;
}

bool game_solve(game g)
{
  uint nb = 0;
  if (game_nb_solutions(g) == 0) {
    return false;
  }
  game_solve_rec(g, 0, &nb, true);
  return true;
}

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