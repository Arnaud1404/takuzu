#ifndef __GAME_AUX_H__
#define __GAME_AUX_H__
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_ext.h"

// affiche le jeu
void game_print(cgame g)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  printf("   ");
  int row = game_nb_rows(g);
  int col = game_nb_cols(g);
  for (int j = 0; j < col; j++) {
    printf("%d", j);
  }
  printf("\n");
  printf("  ------ ");
  printf("\n");

  for (int i = 0; i < row; i++) {
    printf("%d |", i);
    for (int j = 0; j < col; j++) {
      if (game_get_square(g, i, j) == S_EMPTY) {
        printf(" ");
      }
      if (game_get_square(g, i, j) == S_ZERO) {
        printf("w");
      }
      if (game_get_square(g, i, j) == S_ONE) {
        printf("b");
      }
      if (game_get_square(g, i, j) == S_IMMUTABLE_ONE) {
        printf("B");
      }
      if (game_get_square(g, i, j) == S_IMMUTABLE_ZERO) {
        printf("W");
      }
    }
    printf("|\n");
  }
  printf("  ------ \n");
}

// crée et renvoie le jeu par défault
game game_default(void)
{
  game g = game_new_empty();
  game_set_square(g, 0, 1, S_IMMUTABLE_ONE);
  game_set_square(g, 0, 2, S_IMMUTABLE_ZERO);
  game_set_square(g, 2, 1, S_IMMUTABLE_ZERO);
  game_set_square(g, 2, 4, S_IMMUTABLE_ZERO);
  game_set_square(g, 3, 1, S_IMMUTABLE_ZERO);
  game_set_square(g, 3, 2, S_IMMUTABLE_ONE);
  game_set_square(g, 4, 2, S_IMMUTABLE_ONE);
  game_set_square(g, 4, 5, S_IMMUTABLE_ZERO);
  game_set_square(g, 5, 5, S_IMMUTABLE_ZERO);
  return g;
}

// crée et renvoie la solution du jeu par défault
game game_default_solution(void)
{
  game g = game_new_empty();
  game_set_square(g, 0, 0, S_ZERO);
  game_set_square(g, 0, 1, S_IMMUTABLE_ONE);
  game_set_square(g, 0, 2, S_IMMUTABLE_ZERO);
  game_set_square(g, 0, 3, S_ONE);
  game_set_square(g, 0, 4, S_ZERO);
  game_set_square(g, 0, 5, S_ONE);
  game_set_square(g, 1, 0, S_ZERO);
  game_set_square(g, 1, 1, S_ONE);
  game_set_square(g, 1, 2, S_ONE);
  game_set_square(g, 1, 3, S_ZERO);
  game_set_square(g, 1, 4, S_ONE);
  game_set_square(g, 1, 5, S_ZERO);
  game_set_square(g, 2, 0, S_ONE);
  game_set_square(g, 2, 1, S_IMMUTABLE_ZERO);
  game_set_square(g, 2, 2, S_ZERO);
  game_set_square(g, 2, 3, S_ONE);
  game_set_square(g, 2, 4, S_IMMUTABLE_ZERO);
  game_set_square(g, 2, 5, S_ONE);
  game_set_square(g, 3, 0, S_ONE);
  game_set_square(g, 3, 1, S_IMMUTABLE_ZERO);
  game_set_square(g, 3, 2, S_IMMUTABLE_ONE);
  game_set_square(g, 3, 3, S_ZERO);
  game_set_square(g, 3, 4, S_ZERO);
  game_set_square(g, 3, 5, S_ONE);
  game_set_square(g, 4, 0, S_ZERO);
  game_set_square(g, 4, 1, S_ONE);
  game_set_square(g, 4, 2, S_IMMUTABLE_ONE);
  game_set_square(g, 4, 3, S_ZERO);
  game_set_square(g, 4, 4, S_ONE);
  game_set_square(g, 4, 5, S_IMMUTABLE_ZERO);
  game_set_square(g, 5, 0, S_ONE);
  game_set_square(g, 5, 1, S_ZERO);
  game_set_square(g, 5, 2, S_ZERO);
  game_set_square(g, 5, 3, S_ONE);
  game_set_square(g, 5, 4, S_ONE);
  game_set_square(g, 5, 5, S_IMMUTABLE_ZERO);
  return g;
}

#endif  // __GAME_AUX_H__
