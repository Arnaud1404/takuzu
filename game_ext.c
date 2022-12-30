#include <stdbool.h>
#include <stdlib.h>
#include "game.h"
#include "game_struct.h"
#include "queue.h"

struct game_s {
  square* tab;
  int col;
  int row;
  bool wrap;
  bool uni;
};

typedef struct game_s* game;


game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping, bool unique){
        game g = (game)malloc(sizeof(game));
        square* tableau = malloc(sizeof(square) * nb_cols*nb_rows);
        if (g == NULL || tableau == NULL) {
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < nb_cols*nb_rows; i++) {
            tableau[i] = squares[i];
        }
        g->tab = tableau;
        g->col = nb_cols;
        g->row = nb_rows;
        g->uni = unique;
        g->wrap = wrapping;
        return g;
}

game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping, bool unique){
  square* tableau = malloc(sizeof(square) * nb_cols*nb_rows);
  if (tableau == NULL) {
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < nb_cols*nb_rows; i++) {
    tableau[i] = S_EMPTY;
  }
  game g = game_new_ext(nb_rows,nb_cols,tableau,wrapping,unique);
  return g;

}

uint game_nb_rows(cgame g){
    return g->row;
}

uint game_nb_cols(cgame g){
    return g->col;
}

bool game_is_wrapping(cgame g){
    return g->wrap;
}

bool game_is_unique(cgame g){
    return g->uni;
}

void game_undo(game g){

}

void game_redo(game g){

}