/**
 * @file game.h
 * @brief Basic Game Functions.
 * @details See @ref index for further details.
 * @copyright University of Bordeaux. All rights reserved, 2021.
 **/

#ifndef __GAME_H__
#define __GAME_H__

#include <stdbool.h>

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
game game_new(square* squares);

/**
 * @brief Creates a new empty game with defaut size.
 * @details All squares are initialized with empty squares.
 * @return the created game
 **/
game game_new_empty(void);

/**
 * @brief Duplicates a game.
 * @param g the game to copy
 * @return the copy of the game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
game game_copy(cgame g);

/**
 * @brief Tests if two games are equal.
 * @param g1 the first game
 * @param g2 the second game
 * @return true if the two games are equal, false otherwise
 * @pre @p g1 must be a valid pointer toward a game structure.
 * @pre @p g2 must be a valid pointer toward a game structure.
 **/
bool game_equal(cgame g1, cgame g2);

/**
 * @brief Deletes the game and frees the allocated memory.
 * @param g the game to delete
 * @pre @p g must be a valid pointer toward a game structure.
 **/
void game_delete(game g);

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
void game_set_square(game g, uint i, uint j, square s);

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
square game_get_square(cgame g, uint i, uint j);

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
int game_get_number(cgame g, uint i, uint j);

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
int game_get_next_square(cgame g, uint i, uint j, direction dir, uint dist);

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
int game_get_next_number(cgame g, uint i, uint j, direction dir, uint dist);

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
bool game_is_empty(cgame g, uint i, uint j);

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
bool game_is_immutable(cgame g, uint i, uint j);

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
int game_has_error(cgame g, uint i, uint j);

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
bool game_check_move(cgame g, uint i, uint j, square s);

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
void game_play_move(game g, uint i, uint j, square s);

/**
 * @brief Checks if the game is won.
 * @param g the game
 * @details This function checks that all the game rules (decribed on @ref
 * index) are satisfied.
 * @return true if the game ended successfully, false otherwise
 * @pre @p g must be a valid pointer toward a game structure.
 **/
bool game_is_over(cgame g);

/**
 * @brief Restarts a game.
 * @details All the game is reset to its initial state. In particular, all the
 * squares except immutable are reset to empty.
 * @param g the game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
void game_restart(game g);

#endif  // __GAME_H__
