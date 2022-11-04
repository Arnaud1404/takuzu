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



int main(void){
bool ok1 = test_is_over();
bool ok2 = test_game_restart();
if (ok1&&ok2){
    return EXIT_SUCCESS;
}return EXIT_FAILURE;
}