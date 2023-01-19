#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_ext.h"
#include "game_struct.h"
#include "queue.h"

//crée un nouveau jeu avec les paramètre de la v1
game game_new(square* squares)
{
  game g = (game)malloc(sizeof(game));
  square* tableau = malloc(sizeof(square) * DEFAULT_SIZE * DEFAULT_SIZE);
  if (g == NULL || tableau == NULL) {
    free(g);
    free(tableau);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
    tableau[i] = squares[i];
  }
  g->row = DEFAULT_SIZE;
  g->col = DEFAULT_SIZE;
  g->wrap = false;
  g->uni = false;
  g->tab = tableau;
  queue* s = queue_new();
  queue* t = queue_new();
  if (s == NULL || t == NULL) {
    free(g);
    free(tableau);
    free(s);
    free(t);
    exit(EXIT_FAILURE);
  }
  g->to_redo = s;
  g->to_undo = t;
  return g;
}

//crée un nouveau jeu vide avec les paramètre de la v1
game game_new_empty(void)
{
  game g = malloc(sizeof(game));
  square* tableau = malloc(sizeof(square) * DEFAULT_SIZE * DEFAULT_SIZE);
  if (g == NULL || tableau == NULL) {
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
    tableau[i] = S_EMPTY;
  }
  g->tab = tableau;
  g->to_redo = queue_new();
  g->to_undo = queue_new();
  g->col = DEFAULT_SIZE;
  g->row = DEFAULT_SIZE;
  g->wrap = false;
  g->uni = false;
  return g;
}

//crée et retourne une copie du jeu passé en paramètre
game game_copy(cgame g)
{
  game g1 = game_new_ext(g->row, g->col, g->tab, g->wrap, g->uni);
  return g1;
}

//vérifie si deux jeux ont la même grille et les mêmes paramètres
bool game_equal(cgame g1, cgame g2)
{
  if (g1->col != g2->col || g1->row != g2->row || g1->wrap != g2->wrap || g1->uni != g2->uni) {
    return false;
  }
  for (int i = 0; i < g1->col * g1->row; i++) {
    if (g1->tab[i] != g2->tab[i]) {
      return false;
    }
  }
  return true;
}

//supprime le jeu passé en paramètre et vide la mémoire
void game_delete(game g)
{
  free(g->tab);
  queue_free(g->to_redo);
  queue_free(g->to_undo);
  free(g);
}

//défini le contenu d'une case avec la case et la valeur définis par l'utilisateur
//avec i la ligne, j la colonne et s le contenu
void game_set_square(game g, uint i, uint j, square s)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  int compteur = i * g->col + j;
  g->tab[compteur] = s;
}

//cherche et renvoie le contenu d'une case entrée en paramètre
//avec i la ligne, j la colonne et s le contenu
square game_get_square(cgame g, uint i, uint j)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  if (i > g->row || j > g->col) {
    exit(EXIT_FAILURE);
  }
  int compteur = i * g->col + j;
  return g->tab[compteur];
}

//cherche et renvoie la valeur d'une case entrée en paramètre
int game_get_number(cgame g, uint i, uint j)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  if (i > g->row || j > g->col) {
    exit(EXIT_FAILURE);
  }
  int compteur = i * g->col + j;
  square s = g->tab[compteur];
  if (s == S_EMPTY) {
    return -1;
  }
  if (s == S_ZERO || s == S_IMMUTABLE_ZERO) {
    return 0;
  }
  return 1;
}

//cherche et renvoie le contenu d'une case qui suit celle entrée en paramètre
//avec i la ligne, j la colonne, dir la direction et dist la distance
int game_get_next_square(cgame g, uint i, uint j, direction dir, uint dist)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  if (g->wrap == false) {
    if (i > g->row || j > g->col) {
      exit(EXIT_FAILURE);
    }
  }
  if (dist > 2) {
    exit(EXIT_FAILURE);
  }
  if (g->wrap == false) {
    if (dir == DOWN) {
      if (i + dist > 5) {
        return -1;
      }
      return game_get_square(g, i + dist, j);
    }
    if (dir == UP) {
      int m = i - dist;
      if (m < 0) {
        return -1;
      }
      return game_get_square(g, i - dist, j);
    }
    if (dir == RIGHT) {
      if (j + dist > 5) {
        return -1;
      }
      return game_get_square(g, i, j + dist);
    }
    if (dir == LEFT) {
      int d = j - dist;
      if (d < 0) {
        return -1;
      }
      return game_get_square(g, i, j - dist);
    }
  } else {
    if (dir == UP) {
      if (i < dist) {
        i = g->row - dist + i;
      }
      i = i % (g->row);
      j = j % g->col;
      return game_get_square(g, i, j);
    }
    if (dir == DOWN) {
      i = i + dist;
      i = i % g->row;
      j = j % g->col;
      return game_get_square(g, i, j);
    }
    if (dir == RIGHT) {
      i = i % g->row;
      j = j + dist;
      j = j % g->col;
      return game_get_square(g, i, j);
    }
    if (dir == LEFT) {
      if (j < dist) {
        j = g->col - dist + j;
      }
      i = i % g->row;
      j = j % (g->col);
      return game_get_square(g, i, j);
    }
  }
  return -1;
}

//cherche et renvoie la valeur d'une case qui suit celle entrée en paramètre
//avec i la ligne, j la colonne, dir la direction et dist la distance
int game_get_next_number(cgame g, uint i, uint j, direction dir, uint dist)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  if (g->wrap == false) {
    if (i > g->row || j > g->col) {
      exit(EXIT_FAILURE);
    }
  }
  if (dist > 2) {
    exit(EXIT_FAILURE);
  }
  square s = game_get_next_square(g, i, j, dir, dist);
  if (s == S_IMMUTABLE_ONE || s == S_ONE) {
    return 1;
  }
  if (s == S_ZERO || s == S_IMMUTABLE_ZERO) {
    return 0;
  }
  return -1;
}

//test si une case rentrée en paramètre est vide
bool game_is_empty(cgame g, uint i, uint j)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  int compteur;
  compteur = g->row * i + j;
  if (g->tab[compteur] == S_EMPTY) {
    return true;
  }
  return false;
}

//test si la case rentrée en paramètre peut être modifiée
bool game_is_immutable(cgame g, uint i, uint j)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  int compteur = i * g->row + j;
  if (g->tab[compteur] == S_IMMUTABLE_ZERO || g->tab[compteur] == S_IMMUTABLE_ONE) {
    return true;
  }
  return false;
}

int game_donne_nombre(square s)
{
  if (s == S_IMMUTABLE_ONE || s == S_ONE) {
    return 1;
  }
  if (s == S_IMMUTABLE_ZERO || s == S_ZERO) {
    return 0;
  }
  return -1;
}

//test si la case entrée en paramètre a une erreur
int game_has_error(cgame g, uint i, uint j)
{
  int cpt_zero = 0;
  int cpt_one = 0;
  int consecutive_zero = 0;
  int consecutive_one = 0;
  for (int c = 0; c < g->row; c++) {
    if (game_get_number(g, c, j) == 1) {
      cpt_one = cpt_one + 1;
      consecutive_one += 1;
      if (consecutive_one == 3) {
        return true;
      }
      if (consecutive_zero != 0) {
        consecutive_zero = 0;
      }
    } else if (game_get_number(g, c, j) == 0) {
      cpt_zero = cpt_zero + 1;
      consecutive_zero += 1;
      if (consecutive_zero == 3) {
        return true;
      }
      if (consecutive_one != 0) {
        consecutive_one = 0;
      }
    } else {
      consecutive_one = 0;
      consecutive_zero = 0;
    }
    if (cpt_zero > g->row/ 2 || cpt_one > g->row / 2) {
      return true;
    }
  }

  cpt_zero = 0;
  cpt_one = 0;
  consecutive_zero = 0;
  consecutive_one = 0;
  for (int c = 0; c < g->col; c++) {
    if (game_get_number(g, i, c) == 1) {
      cpt_one = cpt_one + 1;
      consecutive_one += 1;
      if (consecutive_one == 3) {
        return true;
      }
      if (consecutive_zero != 0) {
        consecutive_zero = 0;
      }
    } else if (game_get_number(g, i, c) == 0) {
      cpt_zero = cpt_zero + 1;
      consecutive_zero += 1;
      if (consecutive_zero == 3) {
        return true;
      }
      if (consecutive_one != 0) {
        consecutive_one = 0;
      }
    } else {
      consecutive_one = 0;
      consecutive_zero = 0;
    }
    if (cpt_zero > g->col / 2 || cpt_one > g->col / 2) {
      return true;
    }
  }
  if (g->wrap == true) {
    int s1;
    int s2;
    int s3;
    for (int c = 0; c < g->row; c++) {
      s1 = game_get_number(g, c, j);
      s2 = game_get_next_number(g, c, j, UP, 1);
      s3 = game_get_next_number(g, c, j, UP, 2);
      if (s1== 0 && s2 == 0 && s3 == 0) {
        return 1;
      }
      if(s1 == 1 && s2 == 1 && s3 == 1){
        return 1;
      }
    }
    for (int c = 0; c < g->col; c++) {
      s1 = game_get_number(g, c, j);
      s2 = game_get_next_number(g, c, j, RIGHT, 1);
      s3 = game_get_next_number(g, c, j, RIGHT, 2);
      if (s1== 0 && s2 == 0 && s3 == 0) {
        return 1;
      }
      if(s1 == 1 && s2 == 1 && s3 == 1){
        return 1;
      }
    }
  }
  if (g->uni == true) {
    uint c = 0;
    for (uint v = 0; v < g->col; v++) {
      if (v != j) {
        for (uint y = 0; y < g->row; y++) {
          if (game_get_number(g, y, v) == game_get_number(g, y, j) && game_get_number(g, y, j) != -1) c++;
        }
        if (c == g->row) return true;
        c = 0;
      }
    }

    // Ligne non unique
    for (uint v = 0; v < g->row; v++) {
      if (v != i) {
        for (uint y = 0; y < g->col; y++) {
          if (game_get_number(g, v, y) == game_get_number(g, i, y) && game_get_number(g, i, y) != -1) c++;
        }
        if (c == g->col) return true;
        c = 0;
      }
    }
  }

  return false;
}

//test si le coup peut être joué
bool game_check_move(cgame g, uint i, uint j, square s)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  if (g->wrap == false) {
    if (i < 0 || j < 0 || i >= g->row || j >= g->col) {
      return false;
    }
    if (s != S_EMPTY && s != S_ONE && s != S_ZERO) {
      return false;
    }
  }
  i = i % g->row;
  j = j % g->col;
  int compteur = i * g->row + j;
  if (g->tab[compteur] == S_IMMUTABLE_ZERO || g->tab[compteur] == S_IMMUTABLE_ONE) {
    return false;
  }
  return true;
}

//joue le coup demandé dans la case entrée en paramètre
void game_play_move(game g, uint i, uint j, square s)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  if (game_check_move(g, i, j, s) == true) {
    i = i % g->col;
    j = j % g->row;

    // store previous state
    square old = game_get_square(g, i, j);
    move_t old_move = {old, i, j};
    queue_push_head(g->to_undo, &old_move);

    game_set_square(g, i, j, s);

    queue_clear(g->to_redo);
  }
}

//test si le jeu est gagné
bool game_is_over(cgame g)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  if (g->tab == NULL) {
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < g->row * g->col; i++) {
    if (g->tab[i] == S_EMPTY) {
      return false;
    }
  }
  for (int i = 0; i < g->row; i++) {
    for (int j = 0; j < g->col; j++) {
      if (game_has_error(g, i, j) == true) {
        return false;
      }
    }
  }

  return true;
}

//redémare le jeu passé en paramètre, toutes les cases non immutables sont vidées
void game_restart(game g)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < g->row; i++) {
    for (int j = 0; j < g->col; j++) {
      if (game_get_square(g, i, j) != S_IMMUTABLE_ONE && game_get_square(g, i, j) != S_IMMUTABLE_ZERO) {
        game_set_square(g, i, j, S_EMPTY);
      }
    }
  }
  queue_clear(g->to_undo);
  queue_clear(g->to_redo);
}
