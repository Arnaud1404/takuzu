/**
 * @file game_random.h
 * @brief Game Random.
 * @details See @ref index for further details.
 * @copyright University of Bordeaux. All rights reserved, 2022.
 *
 **/

#ifndef __GAME_RANDOM_H__
#define __GAME_RANDOM_H__
#include <stdbool.h>
#include <stdio.h>

#include "game.h"


/**
 * Create a random game with a given size and number of walls
 *
 * @param nb_rows the number of rows of the game
 * @param nb_cols the number of columns of the game
 * @param wrapping wrapping option
 * @param uniq unique option
 * @param with_solution if true, the game contains the solution, otherwise only walls
 *
 * @return the generated random game
 */
game game_random(uint nb_rows, uint nb_cols, bool wrapping, uint uniq, bool with_solution);


#endif  // __GAME_RANDOM_H__