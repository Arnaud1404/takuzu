/**
 * @file game_aux.h
 * @brief Auxiliarry Game Functions.
 * @details See @ref index for further details.
 * @copyright University of Bordeaux. All rights reserved, 2021.
 **/

#ifndef __GAME_AUX_H__
#define __GAME_AUX_H__
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"

/**
 * @brief Prints a game as text on the standard output stream.
 * @details The different squares are respectively displayed as text, as
 * described in @ref index.
 * @param g the game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
void game_print(cgame g)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  printf("   ");
  for (int j = 0; j < DEFAULT_SIZE; j++) {
    printf("%d", j);
  }
  printf("\n");
  printf("  ------ ");

  for (int i = 0; i < DEFAULT_SIZE; i++) {
    printf("%d |", i);
    for (int j = 0; j < DEFAULT_SIZE; j++) {
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

/**
 * @brief Creates the default game.
 * @details See the description of the default game in @ref index.
 * @return the created game
 **/
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

/**
 * @brief Creates the default game solution.
 * @details See the description of the default game in @ref index.
 * @return the created game
 **/
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
