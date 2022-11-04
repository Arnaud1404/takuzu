#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"

//S_ZERO = white
//S_ONE = black
//S_EMPTY = empty square

bool test_dummy(void){
    return EXIT_SUCCESS;
}

int test_game_has_error(void)
{
  game g = game_default();
  game_play_move(g, 0, 0, S_ONE); //is valid
  bool test1 = game_has_error(g, 0, 0); //false

  game_play_move(g, 5, 2, S_ONE); //is an error (3 black squares column)
  bool test2 = game_has_error(g, 5, 2); //true
  game_play_move(g, 5, 2, S_EMPTY);
  bool test3 = game_has_error(g, 5, 2); //false

  game_play_move(g, 0, 3, S_ONE); //is valid
  bool test4 = game_has_error(g, 0, 3); //false

  game_play_move(g, 0, 4, S_ONE); //is an error (too many black squares row)
  bool test5 = game_has_error(g, 0, 4); //true
  game_play_move(g, 0, 4, S_EMPTY);
  bool test6 = game_has_error(g, 0, 4); //false

  game_play_move(g, 5, 4, S_ZERO);
  game_play_move(g, 5, 3, S_ZERO); // 3 white in a row
  bool test7 = game_has_error(g, 5, 3); //true
  bool test8 = game_has_error(g, 5, 4); //true
  game_play_move(g, 5, 4, S_EMPTY); //removes error
  bool test9 = game_has_error(g, 5, 3); //false
  bool test10 = game_has_error(g, 5, 4); //false

  game_play_move(g, 1, 0, S_ONE);
  game_play_move(g, 3, 0, S_ONE);
  game_play_move(g, 4, 0, S_ONE); //too many black squares (column)
  bool test11 = game_has_error(g, 4, 0); //true
  game_play_move(g, 3, 0, S_EMPTY);
  bool test12 = game_has_error(g, 4, 0); //false


  game_delete(g);
  if(!test1 && test2 && !test3 && !test4 && test5 && !test6 && test7 && test8 && !test9 && !test10 && test11 && !test12){
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
  
}

bool test_game_copy(void){
  game g = game_default();
  game g_copy = game_copy(g);
  for(int i = 0; i <DEFAULT_SIZE; i++){
    for(int j = 0; j <DEFAULT_SIZE;j++){
      square square_original = game_get_square(g,i,j);
      square square_copy = game_get_square(g_copy,i,j);
      if (square_copy != square_original){
        game_delete(g);
        game_delete(g_copy);
        return EXIT_FAILURE;
      }
    }
  }
  game_delete(g);
  game_delete(g_copy);
  return EXIT_SUCCESS;

}

bool test_game_is_immutable{
  game g = game_default();
  bool test1 = game_is_immutable(g, 0,1); //true
  bool test2 = game_is_immutable(g, 0,2); //true
  bool test3 = game_is_immutable(g, 0,0); //false
  game_play_move(g, 0, 4, S_ONE);
  game_play_move(g, 0, 5, S_ZERO);
  bool test4 = game_is_immutable(g, 0,4); //false
  bool test5 = game_is_immutable(g, 0,5); //false

  game_delete(g);
  if (test1 && test2 && !test3 && !test4 && !test5){
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

bool test_game_is_empty(void){

  game g = game_default();
  bool test1 = game_is_empty(g, 0, 0); //true
  bool test2 = game_is_empty(g, 0, 1); //false
  bool test3 = game_is_empty(g, 0, 2); //false
  game_play_move(g, 0, 4, S_ONE);
  game_play_move(g, 0, 5, S_ZERO);
  bool test4 = game_is_empty(g, 0,4); //false
  bool test5 = game_is_empty(g, 0,5); //false
  game_delete(g);
  if (test1 && !test2 && !test3 && !test4 && !test5){
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;

}

bool test_game_equal(void){
  game g = game_default();
  game g2 = game_default();
  bool test1 = game_equal(g, g2); //true
  game_play_move(g, 0, 4, S_ONE);
  bool test2 = game_equal(g, g2); //false

  game_delete(g);
  game_delete(g2);

  if (test1 && !test2) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

bool test_get_next_number(){
  return EXIT_FAILURE;
}

bool test_get_number(){
  game g = game_default();
  int empty = game_get_number(g, 0, 0);
  int zero = game_get_number(g, 0, 2);
  int one = game_get_number(g, 0, 1);
  if (empty != -1 || zero != 0 || one != 1){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

bool test_game_new(){
  return EXIT_FAILURE;
}

bool test_game_get_square(){
  return EXIT_FAILURE;
}


int main(int argc, char* argv[]){
    if (argc == 1){
        return EXIT_FAILURE;
    }
    bool test1 = EXIT_FAILURE;
    if (strcmp("dummy",argv[1])==0){
        test1 = test_dummy();
    }

    bool test2 = test_game_has_error();
    bool test3 = test_game_copy();
    bool test4 = test_game_is_immutable();
    bool test5 = test_game_is_empty();
    bool test6 = test_game_equal();
    bool test7 = test_get_next_number();
    bool test8 = test_get_number();
    bool test9 = test_game_new();
    bool test10 = test_game_get_square();


    if (test1 && test2 && test3 && test4 && test5 && test6 && test7 && test8 && test9 && test10){
      return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
