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
    return true;
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
    return true;
  }
  return false;
  
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
        return false;
      }
    }
  }
  game_delete(g);
  game_delete(g_copy);
  return true;

}

bool test_game_is_immutable(){
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
    return true;
  }
  return false;
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
    return true;
  }
  return false;

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
    return true;
  }
  return false;
}

bool test_get_next_number(){
  game g=game_default();
    if(game_get_next_number(g, 0, 0, RIGHT, 1)!=1){
        game_delete(g);
        return false;
    }
    if(game_get_next_number(g, 0, 3, LEFT, 1)!=0){
        game_delete(g);
        return false;
    }
    game_set_square(g, 3, 4, S_ONE);
    if(game_get_next_number(g, 5, 4, UP, 2)!=1){
        game_delete(g);
        return false;
    }
    game_set_square(g, 5, 0, S_ZERO);
    if(game_get_next_number(g, 3, 0, DOWN, 2)!=0){
        game_delete(g);
        return false;
    }
    if(game_get_next_number(g, 0, 5, DOWN, 2)!=-1){
        game_delete(g);
        return false;
    }
    if(game_get_next_number(g, 3, 2, UP, 2)!=-1){
        game_delete(g);
        return false;
    }
    if(game_get_next_number(g, 1, 0, DOWN, 1)!=-1){
        game_delete(g);
        return false;
    }
    if(game_get_next_number(g, 1, 5, LEFT, 2)!=-1){
        game_delete(g);
        return false;
    }
    if(game_get_next_number(g, 5, 0, RIGHT, 1)!=-1){
        game_delete(g);
        return false;
    }
    game_delete(g);
    return true;
}

bool test_get_number(){
  game g = game_default();
  int empty = game_get_number(g, 0, 0);
  int zero = game_get_number(g, 0, 2);
  int one = game_get_number(g, 0, 1);
  game_delete(g);
  if (empty != -1 || zero != 0 || one != 1){
    return false;
  }
  return true;
}

bool test_game_new(){
  int n = DEFAULT_SIZE*DEFAULT_SIZE;
  square* squares = malloc(n*sizeof(square));
  for(int i = 0; i < n; i++){
    squares[i] = S_EMPTY;
  }
  squares[1] = S_IMMUTABLE_ZERO;
  game g = game_new(squares);
  square immutable_zero = game_get_square(g, 0, 1);
  if (immutable_zero == S_IMMUTABLE_ZERO){
    free(squares);
    game_delete(g);
    return true;
  }
  free(squares);
  game_delete(g);
  return false;
}

bool test_game_get_square(){
  game g = game_default();
  game_play_move(g, 0, 4, S_ONE);
  game_play_move(g, 0, 5, S_ZERO);
  square empty = game_get_square(g,0, 0);
  square zero = game_get_square(g,0, 5);
  square one = game_get_square(g,0, 4);
  square immutable_zero = game_get_square(g,0, 2);
  square immutable_one = game_get_square(g,0, 1);
  if (empty == S_EMPTY && zero == S_ZERO && one == S_ONE && immutable_zero == S_IMMUTABLE_ZERO && immutable_one == S_IMMUTABLE_ONE){
    game_delete(g);
    return true;
  }
  game_delete(g);
  return false;
}

//tests:
    //test_dummy();
    //test_game_has_error();
    //test_game_copy();
    //test_game_is_immutable();
    //test_game_is_empty();
    //test_game_equal();
    //test_get_next_number();
    //test_get_number();
    //test_game_new();
    //test_game_get_square();

int main(int argc, char* argv[]){
   bool test = false;
    if(argc == 2){
        if (strcmp(argv[1], "dummy") == 0){
            if(test_dummy()){
                test = true;
            }
        }
        if (strcmp(argv[1], "test_game_has_error") == 0){
            if(test_game_has_error()){
                test = true;
            }
        }
        else if(strcmp(argv[1],"game_copy") == 0) {
            if(test_game_copy()){
                test = true;
            }
        }
        else if (strcmp(argv[1],"game_is_immutable") == 0){
            if(test_game_is_immutable()) {
                test = true;
            }
        }
        else if (strcmp(argv[1],"game_is_empty") == 0){
            if(test_game_is_empty()) {
                test = test_game_get_next_square();
            }
        }
        else if (strcmp(argv[1],"game_equal") == 0){
            if(test_game_equal()){
                test = true;
            }
        }
        else if (strcmp(argv[1],"get_next_number") == 0){
            if(test_get_next_number()) {
                test = true;
            }
         }
         else if (strcmp(argv[1],"get_number") == 0){
            if(test_get_number()) {
                test = true;
            }
         }
         else if (strcmp(argv[1],"game_new") == 0){
            if(test_game_new()) {
                test = true;
            }
         }
         else if (strcmp(argv[1],"game_get_square") == 0){
            if(test_game_get_square()) {
                test = true;
            }
         }
        else{
            return false;
        }
    }
    if (test == true){
        return true;
    }
    return false;
    

    return false;
}
