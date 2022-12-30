#include <stdbool.h>
#include <stdlib.h>
#include "game.h"


game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping, bool unique){
      game g = (game)malloc(sizeof(game));
      return g;
}

game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping, bool unique){
    game g = (game)malloc(sizeof(game));
      return g;

}

uint game_nb_rows(cgame g){
    return 1;
}

uint game_nb_cols(cgame g){
    return 1;
}

bool game_is_wrapping(cgame g){
    return true;
}

bool game_is_unique(cgame g){
    return false;
}

void game_undo(game g){

}

void game_redo(game g){

}