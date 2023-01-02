#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"

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
  if (game_get_next_square(g, 0, 5, DOWN, 2) != S_EMPTY) {
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
  // if(game_get_next_square(g, 5, 5, RIGHT, 1)!=-1){
  //     game_delete(g);
  //     return EXIT_FAILURE;
  //}

  game_delete(g);
  // wrapping = true
  game g2 = game_new_empty_ext(6, 6, true, true);
  game_set_square(g2, 0, 0, S_ZERO);
  game_set_square(g2, 0, 5, S_ONE);
  game_set_square(g2, 5, 0, S_ZERO);
  if (game_get_next_square(g2, 0, 0, LEFT, 1) != S_ONE) {
    game_delete(g2);
    return EXIT_FAILURE;
  }
  if (game_get_next_square(g2, 0, 0, UP, 1) != S_ZERO) {
    game_delete(g2);
    return EXIT_FAILURE;
  }
  if (game_get_next_square(g2, 5, 0, DOWN, 1) != S_ZERO) {
    game_delete(g2);
    return EXIT_FAILURE;
  }
  if (game_get_next_square(g2, 0, 5, RIGHT, 1) != S_ZERO) {
    game_delete(g2);
    return EXIT_FAILURE;
  }
  game_delete(g2);
  return EXIT_SUCCESS;
}

int test_get_number()
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

int test_game_default()
{
  game g = game_new_empty();
  game def = game_default();
  game_set_square(g, 0, 1, S_IMMUTABLE_ONE);
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
  if (game_equal(g, def) != true) {
    game_delete(g);
    game_delete(def);
    return EXIT_FAILURE;
  }
  game_delete(g);
  game_delete(def);
  return EXIT_SUCCESS;
}

// int test_game_undo(){
//   game g=game_default;
//   game gbis=game_default;
//   game_undo(g);
//   if(g!=gbis){
//     game_delete(g);
//     game_delete(gbis);
//     return EXIT_FAILURE;
//   }
//   game_play_move(g,1,1,S_ONE);
//   game_undo(g);
//   if(g!=gbis){
//     game_delete(g);
//     game_delete(gbis);
//     return EXIT_FAILURE;
//   }
//   game_play_move(g,1,1,S_ONE);
//   game_play_move(gbis,1,1,S_ONE);
//   game_play_move(g,0,0,S_ZERO);
//   if(g!=gbis){
//     game_delete(g);
//     game_delete(gbis);
//     return EXIT_FAILURE;
//   }
//   game_delete(g);
//   game_delete(gbis);
//   return EXIT_SUCCESS;
// }

// int test_game_redo(){
//   game g=game_default();
//   game gbis=game_default();
//   game_undo(g);
//   game_redo(g);
//   if(g!=gbis){
//     game_delete(g);
//     game_delete(gbis);
//     return EXIT_FAILURE;
//   }
//   game_play_move(g,1,1,S_ONE);
//   game_play_move(gbis,1,1,S_ONE);
//   game_undo(g);
//   game_redo(g);
//   if(g!=gbis){
//     game_delete(g);
//     game_delete(gbis);
//     return EXIT_FAILURE;
//   }
//   game_delete(g);
//   game_delete(gbis);
//   return EXIT_SUCCESS;
// }

int main(int argcount, char* argv[])
{
  int test;
  if (argcount == 2) {
    if (strcmp(argv[1], "dummy") == 0) {
      test = test_dummy();
    } else if (strcmp(argv[1], "game_new_empty") == 0) {
      if (test_game_new_empty()) {
        test = test_game_new_empty();
      }
    } else if (strcmp(argv[1], "game_delete") == 0) {
      if (test_game_delete()) {
        test = test_game_delete();
      }
    } else if (strcmp(argv[1], "game_set_square") == 0) {
      if (test_game_set_square()) {
        test = test_game_set_square();
      }
    } else if (strcmp(argv[1], "game_get_next_square") == 0) {
      if (test_game_get_next_square()) {
        test = test_game_get_next_square();
      }
    } else if (strcmp(argv[1], "game_default") == 0) {
      if (test_game_default()) {
        test = test_game_default();
      }

    } else if (strcmp(argv[1], "game_default_solution") == 0) {
      if (test_game_default_solution()) {
        test = test_game_default_solution();
      }
    }
  } else {
    test = EXIT_FAILURE;
  }

  if (test == EXIT_SUCCESS) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}
