#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"


int test_dummy(void){
    return EXIT_SUCCESS;
}

void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

int test_is_over(void){
    game g = game_default_solution();
    game g1 = game_default();
    int test = game_is_over(g);
    int test1 = !game_is_over(g1);
    
        for(int i = 0;i<DEFAULT_SIZE;i++){
            for(int j = 0; j <DEFAULT_SIZE;j++){
                if(i!= 5 && j!=3){
              if(game_get_square(g1,i,j)!= S_IMMUTABLE_ONE && game_get_square(g1,i,j)!= S_IMMUTABLE_ONE){  //vérifie si la case est immutable

             
            
            test1 = !game_is_over(g1);
            if (test1 == EXIT_FAILURE){
                return EXIT_FAILURE;
            }
            game_set_square(g1,i,j,game_get_square(g,i,j));}
            }
            }
        }
        

    game_delete(g);
    game_delete(g1);
    if (test==1 && test1==1){
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;

}



int test_game_restart(void){
    game g = game_default();
    game g2 = game_default_solution();
    game_restart(g2);
    if(game_equal(g,g2)==EXIT_SUCCESS){
        game_delete(g);
        game_delete(g2);
        return EXIT_SUCCESS;
    }
    game_delete(g);
        game_delete(g2);
    return EXIT_FAILURE;
}

int test_play_move(void){
    game g = game_default();
    game g1 = game_default();
    game_play_move(g,0,0,S_ONE);
    game_set_square(g1,0,0,S_ONE);
    if(game_equal(g,g1)==EXIT_FAILURE){
        return EXIT_FAILURE;
    }
    game_play_move(g,0,0,S_ZERO);
    game_set_square(g1,0,0,S_ZERO);
    if(game_equal(g,g1)==EXIT_FAILURE){game_delete(g);game_delete(g1);
        return EXIT_FAILURE;
    }game_delete(g);game_delete(g1);
return EXIT_SUCCESS;
}

int test_check_move(void){
    game g = game_default();
    int test1 = game_check_move(g,DEFAULT_SIZE+1,1,S_ZERO);
    int test8 = game_check_move(g,1,DEFAULT_SIZE+1,S_ZERO); //must be EXIT_FAILURE
    int test9 = game_check_move(g,-1,0,S_ZERO);//EXIT_FAILURE

    int test10 = game_check_move(g,0,-1,S_EMPTY);//EXIT_FAILURE
    int test2 = game_check_move(g,DEFAULT_SIZE-1, DEFAULT_SIZE-1,S_ZERO ); //EXIT_FAILURE
    int test6 = game_check_move(g,DEFAULT_SIZE-1, DEFAULT_SIZE-1,S_ONE ); //EXIT_FAILURE
    int test7 = game_check_move(g,DEFAULT_SIZE-1, DEFAULT_SIZE-1,S_EMPTY );  //must be EXIT_FAILURE bc it is an immutable square
    int test3 = game_check_move(g,0,0,S_ZERO); //must be EXIT_SUCCESS
    int test4 = game_check_move(g,0,0,S_ONE); //must be EXIT_SUCCESS
    int test5 = game_check_move(g,0,0,S_EMPTY); // must be EXIT_SUCCESS
    for(int i = 0; i <DEFAULT_SIZE; i++){
        for(int j=0;j<DEFAULT_SIZE;j++){
            if(game_check_move(g,i,j,S_ZERO)==EXIT_FAILURE ){
                if(game_get_square(g,i,j)!= S_IMMUTABLE_ONE && game_get_square(g,i,j)!= S_IMMUTABLE_ZERO){
                    return EXIT_FAILURE;
                }
            }
        }
    }
    if(test1 == 0 && test8 == 0 && test9 == 0 && test10 == 0 && test2 == 0 && test6 == 0 && test7 == 0 && test3 == 1 && test4 == 1 && test5 == 1){
        game_delete(g);return EXIT_SUCCESS;
    }game_delete(g);
    return EXIT_FAILURE;



}

int test_game_print(void){
    game g = game_default();
    game_print(g);
    if(g == NULL){
        game_delete(g);
        return EXIT_FAILURE;
    }game_delete(g);return EXIT_SUCCESS;
}

int main(int argcount, char *argv[]){
    int test = EXIT_FAILURE;
    if(argcount == 2){
        if (strcmp(argv[1], "dummy") == 0){
            test = test_dummy();
        }
        else if(strcmp(argv[1],"is_over") == 0) {
            test = test_is_over();
        } 
        else if (strcmp(argv[1],"game_restart") == 0){
            test = test_game_restart();
        }
        else if (strcmp(argv[1],"play_move") == 0){
            test = test_play_move();
        }
        else if (strcmp(argv[1],"check_move") == 0){
                test = test_check_move();
        }
        else if (strcmp(argv[1],"game_print") == 0){
                test = test_game_print();
        }
        else{
            test = EXIT_FAILURE;
        }
    
    if(test == EXIT_SUCCESS){
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
