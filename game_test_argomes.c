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
  bool test4 = game_has_error(g, 0, 3); //true

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
  if(!test1 && test2 && !test3 && test4 && test5 && !test6 && test7 && test8 && !test9 && !test10 && test11 && !test12){
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
  
}

int main(int argc, char* argv[]){
    if (argc == 1){
        return EXIT_FAILURE;
    }
    if (strcmp("dummy",argv[1])==0){
        return test_dummy();
    }
    return EXIT_FAILURE;
}
