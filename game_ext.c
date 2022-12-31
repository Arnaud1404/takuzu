#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_struct.h"


game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping, bool unique){
        game g = (game)malloc(sizeof(game));
        square* tableau = malloc(sizeof(square) * nb_cols*nb_rows);
        if (g == NULL || tableau == NULL || nb_rows%2 != 0 || nb_cols%2 !=0) {
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < nb_cols*nb_rows; i++) {
            tableau[i] = squares[i];
        }

        g->col = nb_cols;
        g->row = nb_rows;
        g->uni = unique;
        g->wrap = wrapping;
        queue* s = queue_new();
        queue* t = queue_new();
        if (s == NULL || t== NULL) {
        free(tableau);
        free(s);
        free(t);
        free(g);
        exit(EXIT_FAILURE);
    }
        g->tab = tableau;
        g->to_undo = s;
        g->to_redo = t;
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
  if(g->to_undo==NULL){
    fprintf(stderr,"memory error\n");
    exit(EXIT_FAILURE);
  }
  // if(g->to_undo->length==0){
  //   return;
  // }

}

void game_redo(game g){
  if(g->to_redo==NULL){
    fprintf(stderr,"memory error\n");
    exit(EXIT_FAILURE);
  }
  // if(g->to_redo->length==0){
  //   return;
  // }

}