#include <stdlib.h>
#include <stdio.h>

/**
 * @file game.h
 * @brief Basic Game Functions.
 * @details See @ref index for further details.
 * @copyright University of Bordeaux. All rights reserved, 2021.
 **/

#ifndef __GAME_H__
#define __GAME_H__

#include <stdbool.h>
#include "game.h"

/**
 * @brief Standard unsigned integer type.
 **/
typedef unsigned int uint;

/**
 * @brief Size of the default game grid.
 **/
#define DEFAULT_SIZE 6

/**
 * @brief The different squares used in the game.
 **/
typedef enum {
  S_EMPTY,          /**< an empty square */
  S_ZERO,           /**< a zero square */
  S_ONE,            /**< a one square */
  S_IMMUTABLE_ZERO, /**< an immutable zero square */
  S_IMMUTABLE_ONE,  /**< an immutable one square */
} square;

struct game_s{
    square* tab;
};
/**
 * @brief The four cardinal directions in the game grid.
 **/
typedef enum { UP, DOWN, LEFT, RIGHT } direction;

/**
 * @brief The structure pointer that stores the game state.
 **/
typedef struct game_s* game;

/**
 * @brief The structure constant pointer that stores the game state.
 * @details That means that it is not possible to modify the game using this
 * pointer.
 **/
typedef const struct game_s* cgame;


/**
 * @brief Creates a new game with default size and initializes it.
 * @param squares an array describing the initial state of each square using row-major storage
 * @pre @p squares must be an initialized array of default size squared.
 * @return the created game
 **/
game game_new(square* squares){
    game g = malloc(sizeof(game));
    if(g == NULL){
        exit(EXIT_FAILURE);
    }
    g->tab = squares;
    return g;
}

/**
 * @brief Creates a new empty game with defaut size.
 * @details All squares are initialized with empty squares.
 * @return the created game
 **/
game game_new_empty(void){
   game g = malloc(sizeof(game));
   square* tableau = malloc(sizeof(square)*DEFAULT_SIZE*DEFAULT_SIZE);
   if(g == NULL || tableau == NULL ){
    exit(EXIT_FAILURE);
   }
   for(int i = 0; i < DEFAULT_SIZE*DEFAULT_SIZE; i ++){
    tableau[i] = S_EMPTY;
   }
   g->tab = tableau;
   return g;
}

/**
 * @brief Duplicates a game.
 * @param g the game to copy
 * @return the copy of the game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
game game_copy(cgame g){
    game g1 = malloc(sizeof(game));
    square* tableau = malloc(sizeof(square)*DEFAULT_SIZE*DEFAULT_SIZE);
    g1->tab = tableau;
    for(int i = 0; i <DEFAULT_SIZE*DEFAULT_SIZE;i++){
        g1->tab[i] = g->tab[i];
    }
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
bool game_equal(cgame g1, cgame g2){
    for(int i = 0; i < DEFAULT_SIZE*DEFAULT_SIZE; i ++){
        if(g1->tab[i] != g2->tab[i]){
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
void game_delete(game g){
    if(g->tab != NULL){
        free(g->tab);
    }
    if(g != NULL){
    free(g);}
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
void game_set_square(game g, uint i, uint j, square s){
     if(g==NULL){
        exit(EXIT_FAILURE);
    }
    int compteur = i*6+j;
    g->tab[compteur]=s;
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
square game_get_square(cgame g, uint i, uint j){
    if(g==NULL){
        exit(EXIT_FAILURE);
    }
    int compteur = i*6+j;
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
int game_get_number(cgame g, uint i, uint j){
    if(g==NULL){
        exit(EXIT_FAILURE);
    }
    int compteur = i*6+j;
    square s = g->tab[compteur];
    if (s == S_EMPTY){
        return -1;
    }
    if (s == S_ZERO || s == S_IMMUTABLE_ZERO){
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
int game_get_next_square(cgame g, uint i, uint j, direction dir, uint dist){
    if(g==NULL){
        exit(EXIT_FAILURE);
    }
    if(i<0||j<0||i>5||j>5){
        exit(EXIT_FAILURE);
    }
    if(dist>2){
        exit(EXIT_FAILURE);
    }
    if(dir==DOWN){
        if(i+dist>5){
            return -1;
        }
        return game_get_number(g,i,j+dist);
    }
    if(dir==UP){
        if(i-dist<0){
            return -1;
        }
        return game_get_number(g,i,j-dist);
    }
    if(dir==RIGHT){
        if(j+dist>5){
            return -1;
        }
        return game_get_number(g,i+dist,j);
    }
    if(dir==LEFT){
        if(j-dist<0){
            return -1;
        }}
        return game_get_number(g,i-dist,j);
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
int game_get_next_number(cgame g, uint i, uint j, direction dir, uint dist){
    if(g==NULL){
        exit(EXIT_FAILURE);
    }
    if(i<0||j<0||i>5||j>5){
        exit(EXIT_FAILURE);
    }
    if(dist>2){
        exit(EXIT_FAILURE);
    }
    if(dir==DOWN){
        if(i+dist>5){
            return -1;
        }
        return game_get_number(g,i,j+dist);
    }
    if(dir==UP){
        if(i-dist<0){
            return -1;
        }
        return game_get_number(g,i,j-dist);
    }
    if(dir==RIGHT){
        if(j+dist>5){
            return -1;
        }
        return game_get_number(g,i+dist,j);
    }
    if(dir==LEFT){
        if(j-dist<0){
            return -1;
        }}
        return game_get_number(g,i-dist,j);
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
bool game_is_empty(cgame g, uint i, uint j){
    if(g==NULL){
        exit(EXIT_FAILURE);
    }
    int compteur;
    compteur=6*i+j;
    if (g->tab[compteur] == S_EMPTY){
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
bool game_is_immutable(cgame g, uint i, uint j){
    if(g==NULL){
        exit(EXIT_FAILURE);
    }
    int compteur = i*6+j;
    if (g->tab[compteur] == S_IMMUTABLE_ZERO || g->tab[compteur] == S_IMMUTABLE_ONE){
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
int game_has_error(cgame g, uint i, uint j){
    if (g == NULL){
        exit(EXIT_FAILURE);
    }

    square column[] = {S_EMPTY,S_EMPTY,S_EMPTY,S_EMPTY,S_EMPTY,S_EMPTY};
    for(int a = 0; a < DEFAULT_SIZE; a++){
        column[a] = g->tab[j+6*a]; //gets the j-th column
    }
    int cpt_zero = 0;
    int cpt_one = 0;
    int consecutive_zero = 0;
    int consecutive_one = 0;
    for(int c = 0; c < DEFAULT_SIZE; c++){
        if (column[c] == S_ZERO || column[c] ==S_IMMUTABLE_ZERO){
           cpt_zero++;
           consecutive_zero++;
            if (consecutive_zero == 3){
                return true;
            }
            if (consecutive_one != 0){
                consecutive_one = 0;
            }
        }

            if (column[c] == S_ONE || column[c] == S_IMMUTABLE_ONE){
                cpt_one++;
                consecutive_one++;
            if (consecutive_one >= 3){
                return true;
            }
            if (consecutive_zero != 0){
                consecutive_zero = 0;
                }
            }
            else{
            consecutive_one = 0;
            consecutive_zero=0;}
        
    
    if (cpt_zero != DEFAULT_SIZE / 2 || cpt_one != DEFAULT_SIZE / 2){
        return false;
    }

    square row[]={S_EMPTY,S_EMPTY,S_EMPTY,S_EMPTY,S_EMPTY,S_EMPTY};
    for(int a = 0; a < DEFAULT_SIZE; a++){
        row[a] = g->tab[i*6+a]; //gets the i-th row
    }

    cpt_zero = 0;
    cpt_one = 0;
    consecutive_zero = 0;
    consecutive_one = 0;
    for(int c = 0; c < DEFAULT_SIZE; c++){
        if (row[c] == S_ZERO || row[c] ==S_IMMUTABLE_ZERO){
            cpt_zero++;
            consecutive_zero++;
            if (consecutive_zero == 3){
                return true;
            }
            if (consecutive_one != 0){
                consecutive_one = 0;
            }
        }
            if (row[c] == S_ONE || row[c] == S_IMMUTABLE_ONE){
                cpt_one++;
                consecutive_one++;
            if (consecutive_one == 3){
                return true;
            }
            if (consecutive_zero != 0){
                consecutive_zero = 0;
                }
            }
            else{
            consecutive_zero = 0;
            consecutive_one=0;}
            
        }
        if (cpt_zero != DEFAULT_SIZE / 2 || cpt_one != DEFAULT_SIZE / 2){
            return false;
    }}
    return true;
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
bool game_check_move(cgame g, uint i, uint j, square s){
    if (i < 0 || j < 0 || i >= DEFAULT_SIZE || j >= DEFAULT_SIZE){
        return false;
    }
    if (s != S_EMPTY && s != S_ONE && s != S_ZERO){
        return false;
    }
    if(g==NULL){
        exit(EXIT_FAILURE);
    }
    int compteur = i*6+j;
    if(g->tab[compteur] == S_IMMUTABLE_ZERO || g->tab[compteur] == S_IMMUTABLE_ONE){
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
void game_play_move(game g, uint i, uint j, square s){
    if (g == NULL){
        exit(EXIT_FAILURE);
    }
    if(game_check_move(g,i,j,s)==true){
        game_set_square(g,i,j,s);
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
bool game_is_over(cgame g){
    if (g == NULL){
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i<DEFAULT_SIZE*DEFAULT_SIZE;i++){
        if(g->tab[i] == S_EMPTY){
            return false;
        }
    }
    for(int a = 0; a <DEFAULT_SIZE;a++){
        for(int b = 0; b<DEFAULT_SIZE;b++){
            if(game_has_error(g,a,b)){
                return false;
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
void game_restart(game g){
    if (g == NULL){
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<DEFAULT_SIZE; i++){
        for(int j=0; j<DEFAULT_SIZE; j++){
            if(game_get_square(g,i,j)==S_ONE||game_get_square(g,i,j)==S_ZERO){
                game_set_square(g,i,j,S_EMPTY);
            }
        }
    }
}

#endif  // __GAME_H__

