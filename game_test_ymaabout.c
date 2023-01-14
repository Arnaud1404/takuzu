#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"

int test_dummy(void) { return EXIT_SUCCESS; }

void usage(int argc, char* argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

int test_is_over(void)
{
  game g = game_default_solution();
  game g1 = game_default();
  bool test = game_is_over(g);
  bool test1 = !game_is_over(g1);
  game_set_square(g, 0, 0, S_ONE);
  bool test2 = !game_is_over(g);
  square* tab = {S_ONE,S_ZERO,S_ONE,S_ONE};
  game g2 = game_new_ext(2, 2, tab, false, true);
  bool test3 = game_is_over(g2);
  game_delete(g);
  game_delete(g1);
  if (!test || !test1 || !test2) {
    return EXIT_FAILURE;
  }
  if(g2 == true){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int test_game_restart(void)
{
  game g = game_default();
  game g2 = game_default_solution();
  game_restart(g2);
  if (!game_equal(g, g2)) {
    game_delete(g);
    game_delete(g2);
    return EXIT_FAILURE;
  }
  game_delete(g);
  game_delete(g2);
  return EXIT_SUCCESS;
}

int test_play_move(void)
{
  game g = game_default();
  game g1 = game_default();
  game_play_move(g, 0, 0, S_ONE);
  game_set_square(g1, 0, 0, S_ONE);
  if (game_equal(g, g1) == false) {
    return EXIT_FAILURE;
  }
  game_play_move(g, 0, 0, S_ZERO);
  game_set_square(g1, 0, 0, S_ZERO);
  if (game_equal(g, g1) == false) {
    game_delete(g);
    game_delete(g1);
    return EXIT_FAILURE;
  }
  game_delete(g);
  game_delete(g1);
  return EXIT_SUCCESS;
}

int test_check_move(void)
{
  game g = game_default();
  bool test1 = game_check_move(g, DEFAULT_SIZE + 1, 1, S_ZERO);
  bool test8 = game_check_move(g, 1, DEFAULT_SIZE + 1, S_ZERO);  // must be EXIT_FAILURE
  bool test9 = game_check_move(g, -1, 0, S_ZERO);                // EXIT_FAILURE

  bool test10 = game_check_move(g, 0, -1, S_EMPTY);                             // EXIT_FAILURE
  bool test2 = game_check_move(g, DEFAULT_SIZE - 1, DEFAULT_SIZE - 1, S_ZERO);  // EXIT_FAILURE
  bool test6 = game_check_move(g, DEFAULT_SIZE - 1, DEFAULT_SIZE - 1, S_ONE);   // EXIT_FAILURE
  bool test7 = game_check_move(g, DEFAULT_SIZE - 1, DEFAULT_SIZE - 1,
                               S_EMPTY);           // must be EXIT_FAILURE bc it is an immutable square
  bool test3 = game_check_move(g, 0, 0, S_ZERO);   // must be EXIT_SUCCESS
  bool test4 = game_check_move(g, 0, 0, S_ONE);    // must be EXIT_SUCCESS
  bool test5 = game_check_move(g, 0, 0, S_EMPTY);  // must be EXIT_SUCCESS
  for (int i = 0; i < DEFAULT_SIZE; i++) {
    for (int j = 0; j < DEFAULT_SIZE; j++) {
      if (game_check_move(g, i, j, S_ZERO) == false) {
        if (game_get_square(g, i, j) != S_IMMUTABLE_ONE && game_get_square(g, i, j) != S_IMMUTABLE_ZERO) {
          return EXIT_FAILURE;
        }
      }
    }
  }
  if (test1 == 0 && test8 == 0 && test9 == 0 && test10 == 0 && test2 == 0 && test6 == 0 && test7 == 0 && test3 == 1 &&
      test4 == 1 && test5 == 1) {
    game_delete(g);
    return EXIT_SUCCESS;
  }
  game_delete(g);
  return EXIT_FAILURE;
}

int test_game_print(void)
{
  game g = game_default();
  game_print(g);
  if (g == NULL) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_delete(g);
  return EXIT_SUCCESS;
}
int test_is_wrapping(void)
{
  game g = game_new_empty_ext(8, 4, false, false);
  bool rez = true;

  rez = rez && !game_is_wrapping(g);
  game_delete(g);

  g = game_new_empty_ext(2, 4, true, false);
  rez = rez && game_is_wrapping(g);
  game_delete(g);

  g = game_new_empty_ext(2, 4, true, true);
  rez = rez && game_is_wrapping(g);
  game_delete(g);

  g = game_new_empty_ext(2, 4, false, true);
  rez = rez && !game_is_wrapping(g);
  game_delete(g);

  if (rez == true) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}
int test_game_next_square(void)
{
  square tab[] = {S_EMPTY, S_ONE, S_ONE, S_ZERO, S_ZERO, S_EMPTY, S_ZERO, S_ZERO, S_ONE};
  game g = game_new_ext(3, 3, tab, true, false);
  square s1 = game_get_next_square(g, 3, 3, RIGHT, 1);
  if (s1 != S_ZERO) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int main(int argcount, char* argv[])
{
  int test;
  if (argcount == 2) {
    if (strcmp(argv[1], "dummy") == 0) {
      test = test_dummy();

    } else if (strcmp(argv[1], "play_move") == 0) {
      if (test_play_move()) {
        test = test_play_move();
      }
    } else if (strcmp(argv[1], "check_move") == 0) {
      if (test_check_move()) {
        test = test_check_move();
      }
    } else if (strcmp(argv[1], "next_square") == 0) {
      if (test_game_next_square()) {
        test = test_game_next_square();
      }
    } else if (strcmp(argv[1], "game_print") == 0) {
      if (test_game_print()) {
        test = test_game_print();
      }
    } else if (strcmp(argv[1], "is_wrapping") == 0) {
      if (test_is_wrapping()) {
        test = test_is_wrapping();
      }
    }
    if (test == EXIT_FAILURE) {
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
