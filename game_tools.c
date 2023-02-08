/**
 * @file game_tools.h
 * @brief Game Tools.
 * @details See @ref index for further details.
 * @copyright University of Bordeaux. All rights reserved, 2022.
 *
 **/

#ifndef __GAME_TOOLS_H__
#define __GAME_TOOLS_H__
#include "game_ext.h"
#include "game.h"
#include stdio.h

/**
 * @name Game Tools
 * @{
 */

/**
 * @brief Creates a game by loading its description from a text file.
 * @details See the file format description in @ref index.
 * @param filename input file
 * @return the loaded game
 **/
game game_load(char *filename){
    if (filename == NULL){
        exit(EXIT_FAILURE);
    }
    FILE* file_game = fopen(filename,w);
    if (file_game == NULL){
        exit(EXIT_FAILURE);
    }
    int col;
    int lin;
    int wra;
    int uni;
    int a = fscanf(filename,"%d %d %d %d",&lin,&col,&wra,&uni);
    if(a != 4){
        exit(EXIT_FAILURE);
    }
    char tab[lin][col];
    for(int i = 0; i <lin;i++){

    fgets(tab[i], col+1, filename);
    if(tab[i]==NULL){
        exit(EXIT_FAILURE);
    }
    }
    game new_game =  game_new_ext(lin, col, wra,uni,tab);
    return new_game;
    
}

/**
 * @brief Saves a game in a text file.
 * @details See the file format description in @ref index.
 * @param g game to save
 * @param filename output file
 **/
void game_save(cgame g, char *filename);

/**
 * @}
 */

#endif // __GAME_TOOLS_H__
