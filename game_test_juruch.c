#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"
#define DEFAULT_SIZE 6

bool test_dummy(){
    return EXIT_SUCCESS;
}

bool test_game_new_empty(){
    game g=game_new_empty();
    for(uint ibis=0;ibis<DEFAULT_SIZE;ibis++){
        for(uint jbis=0;jbis<DEFAULT_SIZE;jbis++){
            if(game_is_empty(g, ibis, jbis)!=true)
            return false;
        }
    }
return true;
}

bool test_game_set_square(){

}

bool test_game_default{
    game g=game_new_empty();
    game def=game_default();
    game_set_square(g, 0, 1, S_IMMUTABLE_ONE);
    game_set_square(g, 0, 2, S_IMMUTABLE_ZERO);
    game_set_square(g, 2, 1, S_IMMUTABLE_ZERO);
    game_set_square(g, 2, 4, S_IMMUTABLE_ZERO);
    game_set_square(g, 3, 1, S_IMMUTABLE_ZERO);
    game_set_square(g, 3, 2, S_IMMUTABLE_ONE);
    game_set_square(g, 4, 2, S_IMMUTABLE_ONE);
    game_set_square(g, 4, 5, S_IMMUTABLE_ZERO);
    game_set_square(g, 5, 5, S_IMMUTABLE_ZERO);
    if(game_equal(g, def)!=true){
        return false;
    }
    return true;
}

int main(int argcount, char *argvalue[]){
    if(argcount==1){
        return EXIT_FAILURE;
    }
    if (strcmp("dummy",argvalue[1])==0){
        return EXIT_SUCCESS;
    }
    else{
        return EXIT_FAILURE;
    }
}