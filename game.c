#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_struct.h"
#include "queue.h"

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

/**
 * @brief Creates a new empty game with defaut size.
 * @details All squares are initialized with empty squares.
 * @return the created game
 **/
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

/**
 * @brief Duplicates a game.
 * @param g the game to copy
 * @return the copy of the game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
game game_copy(cgame g)
{
  game g1 = malloc(sizeof(game));
  square* tableau = malloc(sizeof(square) * DEFAULT_SIZE * DEFAULT_SIZE);
  g1->tab = tableau;
  for (int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
    g1->tab[i] = g->tab[i];
  }
  g1->wrap = g->wrap;
  g1->col = g->col;
  g1->row = g->row;
  g1->uni = g->uni;
  return g1;
}

/**
 * @brief Tests if two games are equal.
 * @param g1 the first game
 * @param g2 the second game
 * @return true if the two games are equal, false otherwise
 * @pre @p g1 must be a valid pointer toward a game structure.
 * @pre @p g2 must be a valid pointer toward a game structure.
 **/
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

/**
 * @brief Deletes the game and frees the allocated memory.
 * @param g the game to delete
 * @pre @p g must be a valid pointer toward a game structure.
 **/
void game_delete(game g)
{
  free(g->tab);
  queue_free(g->to_redo);
  queue_free(g->to_undo);
  free(g);
}

/**
 * @brief Sets the value of a given square.
 * @details This function is useful for initializing the squares of an empty
 * game.
 * @param g the game
 * @param i row index
 * @param j column index
 * @param s the square value
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @pre @p s must be a valid square value.
 **/
void game_set_square(game g, uint i, uint j, square s)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  int compteur = i * g->col + j;
  g->tab[compteur] = s;
}

/**
 * @brief Gets the value of a given square.
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @return the square value
 **/
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

/**
 * @brief Gets the square number (immutable or not).
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @return the number of this square (0 or 1), or -1 if it is empty
 **/
int game_get_number(cgame g, uint i, uint j)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  if (i < 0 || j < 0 || i > 5 || j > 5) {
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

/**
 * @brief Gets the value of the next square in a given direction.
 * @param g the game
 * @param i row index
 * @param j column index
 * @param dir the direction to the targeted square
 * @param dist the distance to the targeted square
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @pre @p dist <= 2
 * @return the value of the targeted square, or -1 if this square is out
 * of the grid
 **/
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
  if (dir == DOWN) {
    if (g->wrap == false) {
      if (i + dist > g->row) {
        return -1;
      }
      return game_get_square(g, i + dist, j);
    }
    i = (i + dist) % g->row;
    return game_get_square(g, i, j);
  }

  if (dir == UP) {
    if (g->wrap == false) {
      int m = i - dist;
      if (m < 0) {
        return -1;
      }
      return game_get_square(g, i - dist, j);
    }
    i = (i - dist) % g->row;
    return game_get_square(g, i, j);
  }

  if (dir == RIGHT) {
    if (g->wrap == false) {
      if (j + dist > g->col) {
        return -1;
      }
      return game_get_square(g, i, j + dist);
    }
    j = (j + dist) % g->col;
    return game_get_square(g, i, j);
  }

  if (dir == LEFT) {
    if (g->wrap == false) {
      int d = j - dist;
      if (d < 0) {
        return -1;
      }
      return game_get_square(g, i, j - dist);
    }
    j = (j - dist) % g->col;
    return game_get_square(g, i, j);
  }
  return -1;
}

/**
 * @brief Gets the value of the next square in a given direction.
 * @param g the game
 * @param i row index
 * @param j column index
 * @param dir the direction to the targeted square
 * @param dist the distance to the targeted square
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @pre @p dist <= 2
 * @return the number of the targeted square (0 or 1), or -1 if this square is
   empty or out of the grid
 **/
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

  if (dir == DOWN) {
    if (g->wrap == false) {
      if (i + dist > g->row) {
        return -1;
      }
      return game_get_number(g, i + dist, j);
    }
    i = (i + dist) % g->row;
    return game_get_number(g, i, j);
  }

  if (dir == UP) {
    if (g->wrap == false) {
      int m = i - dist;
      if (m < 0) {
        return -1;
      }
      return game_get_number(g, i - dist, j);
    }
    i = (i - dist) % g->row;
    return game_get_number(g, i, j);
  }

  if (dir == RIGHT) {
    if (g->wrap == false) {
      if (j + dist > g->col) {
        return -1;
      }
      return game_get_number(g, i, j + dist);
    }
    j = (j + dist) % g->col;
    return game_get_number(g, i, j);
  }

  if (dir == LEFT) {
    if (g->wrap == false) {
      int d = j - dist;
      if (d < 0) {
        return -1;
      }
      return game_get_number(g, i, j - dist);
    }
    j = (j - dist) % g->col;
    return game_get_number(g, i, j);
  }
  return EXIT_FAILURE;
}

/**
 * @brief Test if a given square is empty.
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @return true if the square is empty
 **/
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

/**
 * @brief Test if a given square is immutable.
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @return true if the square is immutable
 **/
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

/**
 * @brief Test if a given square has an error
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @return an integer error code or 0 if there are no errors.
 **/
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
int game_has_error(cgame g, uint i, uint j)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }

  square* column = {S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY};
  for (int a = 0; a < DEFAULT_SIZE; a++) {
    column[a] = g->tab[j + 6 * a];

    // gets the j-th column
  }
  int cpt_zero = 0;
  int cpt_one = 0;
  int consecutive_zero = 0;
  int consecutive_one = 0;
  for (int c = 0; c < DEFAULT_SIZE; c++) {
    if (column[c] == S_ZERO || column[c] == S_IMMUTABLE_ZERO) {
      cpt_zero = cpt_zero + 1;
      consecutive_zero = consecutive_zero + 1;
      if (consecutive_zero == 3) {
        return true;
      }
      if (consecutive_one != 0) {
        consecutive_one = 0;
      }
    }

    if (column[c] == S_ONE || column[c] == S_IMMUTABLE_ONE) {
      cpt_one = cpt_one + 1;
      consecutive_one += 1;
      printf("ok %d\n", consecutive_one);
      if (consecutive_one == 3) {
        return true;
      }
      if (consecutive_zero != 0) {
        consecutive_zero = 0;
      }
    } else {
      if (column[c] == S_EMPTY) {
        consecutive_one = 0;
        consecutive_zero = 0;
      }
    }
    if (cpt_zero > DEFAULT_SIZE / 2 || cpt_one > DEFAULT_SIZE / 2) {
      return true;
    }
  }

  square row[] = {S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY};
  for (int a = 0; a < DEFAULT_SIZE; a++) {
    row[a] = g->tab[i * 6 + a];  // gets the i-th row
    int b = game_donne_nombre(row[a]);
    printf(" %d", b);
  }
  printf(" \n");
  cpt_zero = 0;
  cpt_one = 0;
  consecutive_zero = 0;
  consecutive_one = 0;
  for (int c = 0; c < DEFAULT_SIZE; c++) {
    printf("%d\n", consecutive_zero);
    if (row[c] == S_ZERO || row[c] == S_IMMUTABLE_ZERO) {
      cpt_zero = cpt_zero + 1;
      consecutive_zero = consecutive_zero + 1;
      if (consecutive_zero == 3) {
        return true;
      }
      if (consecutive_one != 0) {
        consecutive_one = 0;
      }
    }
    if (row[c] == S_ONE || row[c] == S_IMMUTABLE_ONE) {
      cpt_one += 1;
      consecutive_one += 1;
      if (consecutive_one == 3) {
        return true;
      }
      if (consecutive_zero != 0) {
        consecutive_zero = 0;
      }
    } else {
      if (row[c] == S_EMPTY) {
        consecutive_zero = 0;
        consecutive_one = 0;
      }
    }

    if (cpt_zero > DEFAULT_SIZE / 2 || cpt_one > DEFAULT_SIZE / 2) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Checks if a given move is legal.
 * @details This function checks that it is possible to play a move at a given
 * position in the grid. More precisely, a move is said to be legal: 1) if the
 * coordinates (i,j) are inside the grid, 2) if the square @p s is either an
 * empty, zero or one, and 3) if the current square at (i,j) is not an immutable
 * square.
 * @param g the game
 * @param i row index
 * @param j column index
 * @param s the square value
 * @pre @p g must be a valid pointer toward a game structure.
 * @return false if the move is not legal.
 **/
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

/**
 * @brief Plays a move in a given square.
 * @param g the game
 * @param i row index
 * @param j column index
 * @param s the square value
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @pre @p s must be either empty, zero or one.
 * @pre The square at position (i,j) must not be an immutable square.
 **/
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

/**
 * @brief Checks if the game is won.
 * @param g the game
 * @details This function checks that all the game rules (decribed on @ref
 * index) are satisfied.
 * @return true if the game ended successfully, false otherwise
 * @pre @p g must be a valid pointer toward a game structure.
 **/
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
  for (int a = 0; a < g->row; a++) {
    for (int b = 0; b < g->col; b++) {
      if (game_has_error(g, a, b)) {
        return false;
      }
    }
  }
  if (g->uni == true) {
    for (int i = 0; i < g->row - 1; i++) {
      
        int same = 0;
        for (int j = 0; j < g->col; j++) {
          for(int k=1; k< (g->row)-i-1;k++){
          if (game_get_number(g, i, j) == game_get_number(g, i+k, j)) {
            same += 1;
          }
          if (same == g->col) {
            return false;
          }
        }
      }
    }
    for (int i = 0; i < g->col - 1; i++) {
      
        int same = 0;
        for (int j = 0; j < g->row; j++) {
          for(int k=1; k< (g->col)-i-1;k++){
          if (game_get_number(g, j, i) == game_get_number(g, j , i+k)) {
          same += 1;
          }
          if (same == g->row) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

/**
 * @brief Restarts a game.
 * @details All the game is reset to its initial state. In particular, all the
 * squares except immutable are reset to empty.
 * @param g the game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
void game_restart(game g)
{
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < g->row; i++) {
    for (int j = 0; j < g->col; j++) {
      if (game_get_square(g, i, j) == S_ONE || game_get_square(g, i, j) == S_ZERO) {
        game_set_square(g, i, j, S_EMPTY);
      }
    }
  }
  queue_clear(g->to_undo);
  queue_clear(g->to_redo);
}
