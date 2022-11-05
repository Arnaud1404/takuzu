#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"


bool test_dummy(void){
    return true;
}

void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

bool test_is_over(void){
    game g = game_default_solution();
    game g1 = game_default();
    bool test = game_is_over(g);
    bool test1 = !game_is_over(g1);
    
        for(int i = 0;i<DEFAULT_SIZE;i++){
            for(int j = 0; j <DEFAULT_SIZE;j++){
                if(i!= 5 && j!=3){
              if(game_get_square(g1,i,j)!= S_IMMUTABLE_ONE && game_get_square(g1,i,j)!= S_IMMUTABLE_ONE){  //vérifie si la case est immutable

             
            
            test1 = !game_is_over(g1);
            if (test1 == false){
                return false;
            }
            game_set_square(g1,i,j,game_get_square(g,i,j));}
            }
            }
        }
        

    game_delete(g);
    game_delete(g1);
    if (test==1 && test1==1){
        return true;
    }
    return false;

}



bool test_game_restart(void){
    game g = game_default();
    game g2 = game_default_solution();
    game_restart(g2);
    if(game_equal(g,g2)==true){
        game_delete(g);
        game_delete(g2);
        return true;
    }
    game_delete(g);
        game_delete(g2);
    return false;
}

bool test_play_move(void){
    game g = game_default();
    game g1 = game_default();
    game_play_move(g,0,0,S_ONE);
    game_set_square(g1,0,0,S_ONE);
    if(game_equal(g,g1)==false){
        return false;
    }
    game_play_move(g,0,0,S_ZERO);
    game_set_square(g1,0,0,S_ZERO);
    if(game_equal(g,g1)==false){game_delete(g);game_delete(g1);
        return false;
    }game_delete(g);game_delete(g1);
return true;
}

bool test_check_move(void){
    game g = game_default();
    bool test1 = game_check_move(g,DEFAULT_SIZE+1,1,S_ZERO);
    bool test8 = game_check_move(g,1,DEFAULT_SIZE+1,S_ZERO); //must be false
    bool test9 = game_check_move(g,-1,0,S_ZERO);//false

    bool test10 = game_check_move(g,0,-1,S_EMPTY);//false
    bool test2 = game_check_move(g,DEFAULT_SIZE-1, DEFAULT_SIZE-1,S_ZERO ); //false
    bool test6 = game_check_move(g,DEFAULT_SIZE-1, DEFAULT_SIZE-1,S_ONE ); //false
    bool test7 = game_check_move(g,DEFAULT_SIZE-1, DEFAULT_SIZE-1,S_EMPTY );  //must be false bc it is an immutable square
    bool test3 = game_check_move(g,0,0,S_ZERO); //must be true
    bool test4 = game_check_move(g,0,0,S_ONE); //must be true
    bool test5 = game_check_move(g,0,0,S_EMPTY); // must be true
    for(int i = 0; i <DEFAULT_SIZE; i++){
        for(int j=0;j<DEFAULT_SIZE;j++){
            if(game_check_move(g,i,j,S_ZERO)==false ){
                if(game_get_square(g,i,j)!= S_IMMUTABLE_ONE && game_get_square(g,i,j)!= S_IMMUTABLE_ZERO){
                    return false;
                }
            }
        }
    }
    if(test1 == 0 && test8 == 0 && test9 == 0 && test10 == 0 && test2 == 0 && test6 == 0 && test7 == 0 && test3 == 1 && test4 == 1 && test5 == 1){
        game_delete(g);return true;
    }game_delete(g);
    return false;



}

bool test_game_print(void){
    game g = game_default();
    game_print(g);
    if(g == NULL){
        game_delete(g);
        return false;
    }game_delete(g);return true;
}

int main(int argcount, char *argv[]){
    bool test = false;
    if(argcount == 2){
        if (strcmp(argv[1], "dummy") == 0){
            if(test_dummy()){
                test = true;
            }
        }
        else if(strcmp(argv[1],"is_over") == 0) {
            if(test_is_over()){
                test = true;
            }
        } 
        else if (strcmp(argv[1],"play_move") == 0){
            if(test_play_move()){
                test = true;
            }
        }
        else if (strcmp(argv[1],"check_move") == 0){
            if(test_check_move()) {
                test = true;
            }
        }
        else if (strcmp(argv[1],"game_print") == 0){
            if(test_game_print()) {
                test = true;
            }
        }
        else{
            return false;
        }
    }
    if (test == true){
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
