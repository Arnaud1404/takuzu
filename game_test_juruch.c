#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"

bool test_dummy(){
    return EXIT_SUCCESS;
}

bool test_game_new_empty(){
    game g=game_new_empty();
    game def=game_default(); //vérifier que la taille de new empty est celle de default
    for(uint i=0;i<DEFAULT_SIZE;i++){
        for(uint j=0;j<DEFAULT_SIZE;j++){
            if(game_is_empty(g, i, j)!=true)
            return false;
        }
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