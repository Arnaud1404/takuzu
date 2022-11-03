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

int test_is_over(void){
    game g = game_default_solution();
    game g1 = game_default();
    bool test = game_is_over(g);
    bool test1 = !game_is_over(g1);
    while(test1){
        for(int i = 0;i<DEFAULT_SIZE;i++){
            for(int j = 0; j <DEFAULT_SIZE;j++){
                 (if i !=4&& j !=2){  //si on remplit cette case, game est vraiment over 
              if(game_get_number(g1,i,j)==-1){  //vérifie si la case est vide

             
            g1 = game_set_square(g1,i,j,game_get_square(g,i,j));
            test1 = !game_is_over(g1);
             }
            }
            }
        }
        
    }
    game_delete(g);
    game_delete(g1);
    if (test && test1){
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;

}



int main(void){
bool ok1 = test_is_over();
if (ok1){
    return EXIT_SUCCESS;
}return EXIT_FAILURE;
}