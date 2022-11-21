/**
 * @file game_aux.h
 * @brief Auxiliarry Game Functions.
 * @details See @ref index for further details.
 * @copyright University of Bordeaux. All rights reserved, 2021.
 **/

#ifndef __GAME_AUX_H__
#define __GAME_AUX_H__
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "game.h"

/**
 * @brief Prints a game as text on the standard output stream.
 * @details The different squares are respectively displayed as text, as
 * described in @ref index.
 * @param g the game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
void game_print(cgame g){
    if(g == NULL){
        exit(EXIT_FAILURE);
    }
    printf("   ");
    for(int j = 0; j <DEFAULT_SIZE;j ++){
        printf("%d",j);
    }
    printf("\n");
    printf("  ------ ");

    for(int i = 0; i < DEFAULT_SIZE ; i++){
        printf("%d |",i);
        for(int j = 0; j < DEFAUlt_SIZE;j++){
            if(game_get_square(g,i,j)==S_EMPTY){
                printf(" ");
            }
            if(game_get_square(g,i,j)==S_ZERO){
                printf("w");
            }
            if(game_get_square(g,i,j)==S_ONE){
                printf("b");
            }
            if(game_get_square(g,i,j)==S_IMMUTABLE_ONE){
                printf("B");
            }
            if(game_get_square(g,i,j)==S_IMMUTABLE_ZERO){
                printf("W");
            }
            
        }printf("|\n");
    }printf("  ------ \n");
}

/**
 * @brief Creates the default game.
 * @details See the description of the default game in @ref index.
 * @return the created game
 **/
game game_default(void){
    game g = malloc(sizeof(g)) ;
    return g;
}

/**
 * @brief Creates the default game solution.
 * @details See the description of the default game in @ref index.
 * @return the created game
 **/
game game_default_solution(void){
    game g1 = malloc(sizeof(game)) ;
    return g1;
}

#endif  // __GAME_AUX_H__
