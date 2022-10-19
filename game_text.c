#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_aux.h"
#define DEFAULT_SIZE 6

void help(void){
    printf("> action : help\n");
    printf("-press 'w <i> <j>' to put a zero/white at square (i,j)\n");
    printf("-press 'b <i> <j>' to put a one/black at square (i,j)\n");
    printf("-press 'e <i> <j>' to empty square (i,j)\n");
    printf("-press 'r' to restart \n");
    printf("-press 'q' to quit \n");
}

int main(void){
    game g=game_default();
    while (game_is_over(g)!=true){
        game_print(g);
        printf("> ? [h for help]\n");
        for(uint i=0;i<DEFAULT_SIZE;i++){
            for(uint j=0;j<DEFAULT_SIZE;j++){
                if((game_has_error(g,i,j)!=0)){
                    printf("Error at square(%u,%u)\n",i,j);
                }
            }
        }
        char charc;
        int retour=scanf(" %c",&charc);
        if (retour!=1){
            help();
        }
        else if(charc=='h'){
            help();
        }
        else if(charc=='r'){
            printf("> action : restart\n");
            game_restart(g);
        }
        else if(charc=='q'){
            printf("> action : quit\n");
            printf("shame\n");
            game_delete(g);
            return EXIT_SUCCESS;
        }
        else if(charc=='w'||charc=='b'||charc=='e'){
            uint it, jt;
            square jouer;
            int retourbis = scanf("%u %u",&it,&jt);
            if (retourbis!=2){
                help();
            }
            else if(charc=='w'){
                jouer=S_ZERO;
                if(game_check_move(g,it,jt,jouer)==true){
                    printf("> action : play move '%c' into square (%u,%u)\n",charc,it,jt);
                    game_play_move(g,it,jt,jouer);
                }
            }
            else if(charc=='b'){
                jouer=S_ONE;
                if(game_check_move(g,it,jt,jouer)==true){
                    printf("> action : play move '%c' into square (%u,%u)\n",charc,it,jt);
                    game_play_move(g,it,jt,jouer);
                }
            }
            else if(charc=='e'){
                jouer=S_EMPTY;
                if(game_check_move(g,it,jt,jouer)==true){
                    game_play_move(g,it,jt,jouer);
                }
            }
        }

    }
    game_print(g);
    printf("congratulation\n");
    game_delete(g);
    return EXIT_SUCCESS;
}