#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"

int test_dummy() { return EXIT_SUCCESS; }

int test_game_new_empty()
{
  game g = game_new_empty();
  for (int i = 0; i < DEFAULT_SIZE; i++) {
    for (int j = 0; j < DEFAULT_SIZE; j++) {
      if (!game_is_empty(g, i, j)) {
        game_delete(g);
        return EXIT_FAILURE;
      }
    }
  }
  game_delete(g);
  return EXIT_SUCCESS;
}

int test_game_delete()
{
  game g = game_default();
  game_delete(g);
  return EXIT_SUCCESS;
}

int test_game_set_square()
{
  game g = game_new_empty();
  game_set_square(g, 0, 0, S_IMMUTABLE_ONE);
  if (game_get_number(g, 0, 0) != 1) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_set_square(g, 0, 0, S_ONE);
  if (game_get_number(g, 0, 0) != 1) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_set_square(g, 0, 0, S_EMPTY);
  if (game_get_number(g, 0, 0) != -1) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_set_square(g, 0, 0, S_ZERO);
  if (game_get_number(g, 0, 0) != 0) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_set_square(g, 0, 0, S_IMMUTABLE_ZERO);
  if (game_get_number(g, 0, 0) != 0) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_delete(g);
  return EXIT_SUCCESS;
}

int test_game_get_next_square()
{
  game g = game_new_empty_ext(6, 6, false, false);

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

  if (game_get_next_square(g, 0, 0, RIGHT, 1) != S_IMMUTABLE_ONE) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  if (game_get_next_square(g, 0, 3, LEFT, 1) != S_IMMUTABLE_ZERO) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_set_square(g, 3, 4, S_ONE);
  if (game_get_next_square(g, 5, 4, UP, 2) != S_ONE) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_set_square(g, 5, 0, S_ZERO);
  if (game_get_next_square(g, 3, 0, DOWN, 2) != S_ZERO) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  if (game_get_next_square(g, 0, 2, UP, 2) != -1) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  if (game_get_next_square(g, 5, 0, DOWN, 1) != -1) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  if (game_get_next_square(g, 1, 1, LEFT, 2) != -1) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  if (game_get_next_square(g, 5, 5, RIGHT, 1) != -1) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_delete(g);

  // wrapping = true
  game g2 = game_new_empty_ext(6, 6, true, true);
  game_set_square(g2, 0, 0, S_ZERO);
  game_set_square(g2, 0, 5, S_ONE);
  game_set_square(g2, 5, 0, S_ZERO);
  if (game_get_next_square(g2, 0, 0, LEFT, 1) == -1) {
    game_delete(g2);
    return EXIT_FAILURE;
  }
  if (game_get_next_square(g2, 0, 0, UP, 1) == -1) {
    game_delete(g2);
    return EXIT_FAILURE;
  }
  if (game_get_next_square(g2, 5, 0, DOWN, 1) == -1) {
    game_delete(g2);
    return EXIT_FAILURE;
  }
  if (game_get_next_square(g2, 0, 5, RIGHT, 1) == -1) {
    game_delete(g2);
    return EXIT_FAILURE;
  }
  game_delete(g2);
  return EXIT_SUCCESS;
}

int test_game_default()
{
  game g = game_new_empty();
  game def = game_default();
  game_set_square(g, 0, 1, S_IMMUTABLE_ONE);  // cases du jeu par défault
  game_set_square(g, 0, 2, S_IMMUTABLE_ZERO);
  game_set_square(g, 2, 1, S_IMMUTABLE_ZERO);
  game_set_square(g, 2, 4, S_IMMUTABLE_ZERO);
  game_set_square(g, 3, 1, S_IMMUTABLE_ZERO);
  game_set_square(g, 3, 2, S_IMMUTABLE_ONE);
  game_set_square(g, 4, 2, S_IMMUTABLE_ONE);
  game_set_square(g, 4, 5, S_IMMUTABLE_ZERO);
  game_set_square(g, 5, 5, S_IMMUTABLE_ZERO);
  if (game_equal(g, def) != true) {
    game_delete(g);
    game_delete(def);
    return EXIT_FAILURE;
  }
  game_delete(g);
  game_delete(def);
  return EXIT_SUCCESS;
}

int test_game_default_solution()
{
  game g = game_new_empty();
  game def = game_default_solution();
  game_set_square(g, 0, 0, S_ZERO);  // cases de la solution du jeu par défault
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
  if (game_equal(g, def) != true) {
    game_delete(g);
    game_delete(def);
    return EXIT_FAILURE;
  }
  game_delete(g);
  game_delete(def);
  return EXIT_SUCCESS;
}

int test_game_nb_solutions()
{
  game g4 = game_load("4x4_90.txt");
  game g4bis = game_copy(g4);
  if (game_nb_solutions(g4) != 90 || game_equal(g4, g4bis) != true) {
    game_delete(g4);
    game_delete(g4bis);
    return EXIT_FAILURE;
  }
  game g6 = game_load("6x6_empty.txt");
  game g6bis = game_copy(g6);
  if (game_nb_solutions(g6) != 11222 || game_equal(g6, g6bis) != true) {
    game_delete(g6);
    game_delete(g6bis);
    return EXIT_FAILURE;
  }
  game_delete(g4);
  game_delete(g4bis);
  game_delete(g6);
  game_delete(g6bis);
  return EXIT_SUCCESS;
}

int test_game_solve()
{
  game g = game_default();
  game gsol = game_default_solution();
  bool b = game_solve(g);
  if (b != true || g != gsol) {
    game_delete(g);
    game_delete(gsol);
    return EXIT_FAILURE;
  }
  game_delete(g);
  game_delete(gsol);
  return EXIT_SUCCESS;
}

int main(int argcount, char* argv[])
{
  int test = 0;
  if (argcount == 2) {
    if (strcmp(argv[1], "dummy") == 0) {
      test = test_dummy();
    } else if (strcmp(argv[1], "game_new_empty") == 0) {
      test = test_game_new_empty();
    } else if (strcmp(argv[1], "game_delete") == 0) {
      test = test_game_delete();
    } else if (strcmp(argv[1], "game_set_square") == 0) {
      test = test_game_set_square();
    } else if (strcmp(argv[1], "game_get_next_square") == 0) {
      test = test_game_get_next_square();
    } else if (strcmp(argv[1], "game_default") == 0) {
      test = test_game_default();
    } else if (strcmp(argv[1], "game_default_solution") == 0) {
      test = test_game_default_solution();
    } else if (strcmp(argv[1], "game_nb_solutions") == 0) {
      test = test_game_nb_solutions();
    } else if (strcmp(argv[1], "game_solve") == 0) {
      test = test_game_solve();
    } else {
      test = EXIT_FAILURE;
    }
    if (test == EXIT_SUCCESS) {
      return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
  }
}
