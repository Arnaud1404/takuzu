#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "queue.h"

// S_ZERO = white
// S_ONE = black
// S_EMPTY = empty square

int test_dummy(void) { return EXIT_SUCCESS; }

int test_game_has_error(void)
{
  game g = game_default();
  game_set_square(g, 0, 0, S_ONE);        // is valid
  bool test1 = !game_has_error(g, 0, 0);  // EXIT_FAILURE

  game_set_square(g, 5, 2, S_ONE);       // is an error (3 black squares column)
  bool test2 = game_has_error(g, 5, 2);  // EXIT_SUCCESS
  game_set_square(g, 5, 2, S_EMPTY);
  bool test3 = !game_has_error(g, 5, 2);  // EXIT_FAILURE

  game_set_square(g, 0, 3, S_ONE);        // is valid
  bool test4 = !game_has_error(g, 0, 3);  // EXIT_FAILURE

  game_set_square(g, 0, 4, S_ONE);       // is an error (too many black squares row)
  bool test5 = game_has_error(g, 0, 4);  // EXIT_SUCCESS
  game_set_square(g, 0, 4, S_EMPTY);
  bool test6 = !game_has_error(g, 0, 4);  // EXIT_FAILURE

  game_set_square(g, 5, 4, S_ZERO);
  game_set_square(g, 5, 3, S_ZERO);        // 3 white in a row
  bool test7 = game_has_error(g, 5, 3);    // EXIT_SUCCESS
  bool test8 = game_has_error(g, 5, 4);    // EXIT_SUCCESS
  game_set_square(g, 5, 4, S_EMPTY);       // removes error
  bool test9 = !game_has_error(g, 5, 3);   // EXIT_FAILURE
  bool test10 = !game_has_error(g, 5, 4);  // EXIT_FAILURE

  game_set_square(g, 1, 0, S_ONE);
  game_set_square(g, 3, 0, S_ONE);
  game_set_square(g, 4, 0, S_ONE);        // too many black squares (column)
  bool test11 = game_has_error(g, 4, 0);  // EXIT_SUCCESS
  game_set_square(g, 3, 0, S_EMPTY);
  bool test12 = !game_has_error(g, 4, 0);  // EXIT_FAILURE

  game_delete(g);
  if (!test1 || !test2 || !test3 || !test4 || !test5 || !test6 || !test7 || !test8 || !test9 || !test10 || !test11 ||
      !test12) {
    return EXIT_FAILURE;
  }
  
  game g2 = game_new_empty_ext(4, 4, true, true);
  game_set_square(g2, 0, 0, S_ONE);
  game_set_square(g2, 1, 0, S_ONE);
  game_set_square(g2, 3, 0, S_ONE);

  bool test13 = game_has_error(g2, 0, 0);
    
  if (!test13) {
    game_delete(g2);
    return EXIT_FAILURE;
  }
  game_set_square(g2,1,0,S_EMPTY);
  bool test14 = game_has_error(g2,0,0);
  game_delete(g2);
  if(test14){
    return EXIT_FAILURE;
  }
  square tab2[] = {S_ONE,S_ZERO,S_ONE,S_ZERO,
                  S_ZERO,S_ONE,S_ZERO,S_ONE,
                  S_ONE,S_ZERO,S_ONE,S_ZERO,
                  S_ZERO,S_ONE,S_ZERO,S_ONE};
  game g3 = game_new_ext(4,4,tab2,false,true);
  bool test15 = game_has_error(g3,0,0);
  game_delete(g3);
  if(!test15){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int test_game_copy(void)
{
  square s[] = {S_EMPTY, S_IMMUTABLE_ONE,  S_IMMUTABLE_ZERO, S_EMPTY, S_EMPTY,          S_EMPTY,
                S_EMPTY, S_EMPTY,          S_EMPTY,          S_EMPTY, S_EMPTY,          S_EMPTY,
                S_EMPTY, S_IMMUTABLE_ZERO, S_EMPTY,          S_EMPTY, S_IMMUTABLE_ZERO, S_EMPTY,
                S_EMPTY, S_IMMUTABLE_ZERO, S_IMMUTABLE_ONE,  S_EMPTY, S_EMPTY,          S_EMPTY,
                S_EMPTY, S_EMPTY,          S_IMMUTABLE_ONE,  S_EMPTY, S_EMPTY,          S_IMMUTABLE_ZERO,
                S_EMPTY, S_EMPTY,          S_EMPTY,          S_EMPTY, S_EMPTY,          S_IMMUTABLE_ZERO};
  square* tableau = malloc(sizeof(square) * 36);
  for (int i = 0; i < 36; i++) {
    tableau[i] = s[i];
  }
  game g = game_new_ext(6, 6, s, true, false);
  game g_copy = game_copy(g);
  if (game_equal(g, g_copy) == false) {
    game_delete(g);
    game_delete(g_copy);
    free(tableau);
    return EXIT_FAILURE;
  }
  free(tableau);
  game_delete(g);
  game_delete(g_copy);
  return EXIT_SUCCESS;
}

int test_game_is_immutable()
{
  game g = game_default();
  bool test1 = game_is_immutable(g, 0, 1);  // EXIT_SUCCESS
  bool test2 = game_is_immutable(g, 0, 2);  // EXIT_SUCCESS
  bool test3 = game_is_immutable(g, 0, 0);  // EXIT_FAILURE
  game_play_move(g, 0, 4, S_ONE);
  game_play_move(g, 0, 5, S_ZERO);
  bool test4 = game_is_immutable(g, 0, 4);  // EXIT_FAILURE
  bool test5 = game_is_immutable(g, 0, 5);  // EXIT_FAILURE

  game_delete(g);
  if (test1 && test2 && !test3 && !test4 && !test5) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int test_game_is_empty(void)
{
  game g = game_default();
  bool test1 = game_is_empty(g, 0, 0);   // EXIT_SUCCESS
  bool test2 = !game_is_empty(g, 0, 1);  // EXIT_FAILURE
  bool test3 = !game_is_empty(g, 0, 2);  // EXIT_FAILURE
  game_play_move(g, 0, 4, S_ONE);
  game_play_move(g, 0, 5, S_ZERO);
  bool test4 = !game_is_empty(g, 0, 4);  // EXIT_FAILURE
  bool test5 = !game_is_empty(g, 0, 5);  // EXIT_FAILURE
  game_delete(g);
  if (test1 && test2 && test3 && test4 && test5) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int test_game_equal()
{
  game g = game_default();
  game g2 = game_default();
  bool test1 = game_equal(g, g2);
  game_set_square(g2, 0, 1, S_ONE);
  bool test2 = game_equal(g, g2);
  game_delete(g);
  game_delete(g2);
  if (test1 == true && test2 == false) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int test_game_get_next_number()
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

  if (game_get_next_number(g, 0, 0, RIGHT, 1) != 1) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  if (game_get_next_number(g, 0, 3, LEFT, 1) != 0) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_set_square(g, 3, 4, S_ONE);
  if (game_get_next_number(g, 5, 4, UP, 2) != 1) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_set_square(g, 5, 0, S_ZERO);
  if (game_get_next_number(g, 3, 0, DOWN, 2) != 0) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  if (game_get_next_number(g, 0, 2, UP, 2) != -1) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  if (game_get_next_number(g, 5, 0, DOWN, 1) != -1) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  if (game_get_next_number(g, 1, 1, LEFT, 2) != -1) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  if (game_get_next_number(g, 5, 5, RIGHT, 1) != -1) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_delete(g);

  // wrapping = true
  game g2 = game_new_empty_ext(6, 6, true, true);
  game_set_square(g2, 0, 0, S_ZERO);
  game_set_square(g2, 0, 5, S_ONE);
  game_set_square(g2, 5, 0, S_ZERO);
  if (game_get_next_number(g2, 0, 0, LEFT, 1) != 1) {
    game_delete(g2);
    return EXIT_FAILURE;
  }
  if (game_get_next_number(g2, 0, 0, UP, 1) != 0) {
    game_delete(g2);
    return EXIT_FAILURE;
  }
  if (game_get_next_number(g2, 5, 0, DOWN, 1) != 0) {
    game_delete(g2);
    return EXIT_FAILURE;
  }
  if (game_get_next_number(g2, 0, 5, RIGHT, 1) != 0) {
    game_delete(g2);
    return EXIT_FAILURE;
  }
  game_delete(g2);
  return EXIT_SUCCESS;
}

int test_game_get_number()
{
  game g = game_default();
  int empty = game_get_number(g, 0, 0);
  int zero = game_get_number(g, 0, 2);
  int one = game_get_number(g, 0, 1);
  game_delete(g);
  if (empty != -1 || zero != 0 || one != 1) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int test_game_new()
{
  int n = DEFAULT_SIZE * DEFAULT_SIZE;
  square* squares = malloc(n * sizeof(square));
  for (int i = 0; i < n; i++) {
    squares[i] = S_EMPTY;
  }
  squares[1] = S_IMMUTABLE_ZERO;
  squares[35] = S_IMMUTABLE_ONE;
  game g = game_new(squares);
  square immutable_zero = game_get_square(g, 0, 1);
  square immutable_one = game_get_square(g, 5, 5);
  square empty = game_get_square(g, 0, 0);
  if (immutable_zero == S_IMMUTABLE_ZERO && immutable_one == S_IMMUTABLE_ONE && empty == S_EMPTY) {
    free(squares);
    game_delete(g);
    return EXIT_SUCCESS;
  }
  free(squares);
  game_delete(g);
  return EXIT_FAILURE;
}

int test_game_get_square()
{
  game g = game_default();
  game_play_move(g, 0, 4, S_ONE);
  game_play_move(g, 0, 5, S_ZERO);
  square empty = game_get_square(g, 0, 0);
  square zero = game_get_square(g, 0, 5);
  square one = game_get_square(g, 0, 4);
  square immutable_zero = game_get_square(g, 0, 2);
  square immutable_one = game_get_square(g, 0, 1);
  if (empty == S_EMPTY && zero == S_ZERO && one == S_ONE && immutable_zero == S_IMMUTABLE_ZERO &&
      immutable_one == S_IMMUTABLE_ONE) {
    game_delete(g);
    return EXIT_SUCCESS;
  }
  game_delete(g);
  return EXIT_FAILURE;
}

int test_game_new_ext()
{
  int n = 8 * 4;
  square* squares = malloc(n * sizeof(square));
  if(squares == NULL){
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < n; i++) {
    squares[i] = S_EMPTY;
  }
  squares[1] = S_IMMUTABLE_ZERO;
  squares[31] = S_IMMUTABLE_ONE;
  game g = game_new_ext(8, 4, squares, true, true);
  square immutable_zero = game_get_square(g, 0, 1);
  square immutable_one = game_get_square(g, 7, 3);
  square empty = game_get_square(g, 0, 0);
  if (!game_is_wrapping(g) || !game_is_unique(g)) {
    free(squares);
    game_delete(g);
    return EXIT_FAILURE;
  }
  if (immutable_zero == S_IMMUTABLE_ZERO && immutable_one == S_IMMUTABLE_ONE && empty == S_EMPTY) {
    free(squares);
    game_delete(g);
    return EXIT_SUCCESS;
  }
  free(squares);
  game_delete(g);
  return EXIT_FAILURE;
}

int test_game_new_empty_ext()
{
  game g = game_new_empty_ext(8, 4, true, true);
  if (!game_is_wrapping(g) || !game_is_unique(g)) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 4; j++) {
      if (game_get_square(g, i, j)!=S_EMPTY) {
        game_delete(g);
        return EXIT_FAILURE;
      }
    }
  }
  game_delete(g);
  return EXIT_SUCCESS;
}

int test_game_nb_rows()
{
  game g = game_new_empty_ext(8, 4, true, true);
  if (game_nb_rows(g) == 8) {
    game_delete(g);
    return EXIT_SUCCESS;
  }
  game_delete(g);
  return EXIT_FAILURE;
}

int test_game_nb_cols()
{
  game g = game_new_empty_ext(8, 4, true, true);
  if (game_nb_cols(g) == 4) {
    game_delete(g);
    return EXIT_SUCCESS;
  }
  game_delete(g);
  return EXIT_FAILURE;
}

int test_game_is_unique()
{
  game g = game_new_empty_ext(8, 4, true, true);
  if (game_is_unique(g)) {
    game_delete(g);
    return EXIT_SUCCESS;
  }
  game_delete(g);
  return EXIT_FAILURE;
}

int test_game_undo()
{
  game g = game_new_empty_ext(8, 4, true, true);
  game_play_move(g, 0, 0, S_ZERO);
  game_play_move(g,1,0,S_ONE);
  game_undo(g);
  if (game_get_square(g, 1, 0) != S_EMPTY) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_undo(g);
  if (game_get_square(g, 0, 0) != S_EMPTY) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_delete(g);
  return EXIT_SUCCESS;
}

int test_game_redo()
{
  game g = game_new_empty_ext(8, 4, true, true);
  game_play_move(g, 0, 0, S_ZERO);
  game_undo(g);
  game_redo(g);

  if (game_get_square(g, 0, 0) != S_ZERO) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_undo(g);
  if (game_get_square(g, 0, 0) != S_EMPTY) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_delete(g);
  return EXIT_SUCCESS;
}
int main(int argcount, char* argv[])
{
  int test = 0;
  if (argcount == 2) {
    if (strcmp(argv[1], "dummy") == 0) {
      test = test_dummy();
    } else if (strcmp(argv[1], "game_has_error") == 0) {
      if (test_game_has_error()) {
        test = test_game_has_error();
      }
    } else if (strcmp(argv[1], "game_copy") == 0) {
      if (test_game_copy()) {
        test = test_game_copy();
      }
    } else if (strcmp(argv[1], "game_is_immutable") == 0) {
      if (test_game_is_immutable()) {
        test = test_game_is_immutable();
      }
    } else if (strcmp(argv[1], "game_is_empty") == 0) {
      if (test_game_is_empty()) {
        test = test_game_is_empty();
      }
    } else if (strcmp(argv[1], "game_equal") == 0) {
      if (test_game_equal()) {
        test = test_game_equal();
      }
    } else if (strcmp(argv[1], "game_get_next_number") == 0) {
      if (test_game_get_next_number()) {
        test = test_game_get_next_number();
      }
    } else if (strcmp(argv[1], "game_get_number") == 0) {
      if (test_game_get_number()) {
        test = test_game_get_number();
      }
    } else if (strcmp(argv[1], "game_new") == 0) {
      if (test_game_new()) {
        test = test_game_new();
      }
    } else if (strcmp(argv[1], "game_get_square") == 0) {
      if (test_game_get_square()) {
        test = test_game_get_square();
      }
    } else if (strcmp(argv[1], "game_new_ext") == 0) {
      if (test_game_new_ext()) {
        test = test_game_new_ext();
      }
    } else if (strcmp(argv[1], "game_new_empty_ext") == 0) {
      if (test_game_new_empty_ext()) {
        test = test_game_new_empty_ext();
      }
    } else if (strcmp(argv[1], "game_nb_rows") == 0) {
      if (test_game_nb_rows()) {
        test = test_game_nb_rows();
      }
    } else if (strcmp(argv[1], "game_nb_cols") == 0) {
      if (test_game_nb_cols()) {
        test = test_game_nb_cols();
      }
    } else if (strcmp(argv[1], "game_is_unique") == 0) {
      if (test_game_is_unique()) {
        test = test_game_is_unique();
      }
    } else if (strcmp(argv[1], "game_undo") == 0) {
      if (test_game_undo()) {
        test = test_game_undo();
      }
    } else if (strcmp(argv[1], "game_redo") == 0) {
      if (test_game_redo()) {
        test = test_game_redo();
      }
    } else {
      test = EXIT_FAILURE;
    }
  }
  if (test == EXIT_SUCCESS) {
    return 0;
  }
  return 1;
}
