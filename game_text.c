#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_aux.h"

void help(void)
{
    printf("> action : help\n");
    printf("-press 'w <i> <j>' to put a zero/white at square (i,j)\n");
    printf("-press 'b <i> <j>' to put a one/black at square (i,j)\n");
    printf("-press 'e <i> <j>' to empty square (i,j)\n");
    printf("-press 'r' to restart \n");
    printf("-press 'q' to quit \n");
}

int main(void)
{
    game g = game_default();
    uint i = 0;
    uint j = 0;
    uint size = DEFAULT_SIZE;
    game_play_move(g, i, j, S_ZERO);
    while (game_is_over(g) == false)
    {
        game_print(g);
        for (int a = 0; a < size; a++)
        {
            for (int b = 0; b < size; b++)
            {
                int v = game_has_error(g, a, b);
                if (v != 0)
                {
                    printf("%d\n", v);
                }
            }
        }
        char charc;
        int retour = scanf(" %c", &charc);
        if (retour != 1)
        {
            help();
        }
        else if (charc == 'h'){
            help();
        }

        else if (charc == 'r')
        {
            game_restart(g);
        }
        else if (charc == 'q')
        {
            game_delete(g);
            printf("shame");
            return (EXIT_SUCCESS);
        }
        else if (charc == 'w' || charc == 'b' || charc == 'e')
        {
            int i, j;
            int entiers = scanf(" %d %d", &i, &j);
            if (entiers != 2)
            {
                help();
            }
            square move;
        
            if (charc == 'w')
            {
                printf("> action : help\n");
                move = S_ZERO;
                if (game_check_move(g, i, j, move) == true)
                {
                    game_play_move(g, i, j, move);
                }
            }
            else if (charc == 'b')
            {
                move = S_ONE;
                if (game_check_move(g, i, j, move) == true)
                {
                    game_play_move(g, i, j, move);
                }
            }
            else if (charc == 'e')
            {
                move = S_EMPTY;
                if (game_check_move(g, i, j, move) == true)
                {
                    game_play_move(g, i, j, move);
                }
            }
        }
    }

    printf("congratulations");
    game_delete(g);
    return (EXIT_SUCCESS);
}
