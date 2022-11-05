#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"

bool test_dummy(){
    return true;
}

bool test_game_new_empty(){
    game g=game_new_empty();
    if (g==NULL){
        return false;
    }
    game_play_move(g, 5, 5, S_ZERO);
    int oob1 = game_get_next_number(g, 5, 5, DOWN, 1);
    int oob2 = game_get_next_number(g, 5, 5, RIGHT, 1); //checks if game is > default size

    int oob3 = game_get_next_number(g, 4, 4, DOWN, 1);
    int oob4 = game_get_next_number(g, 4, 4, RIGHT, 1);//checks if game is < default size
    if(oob1 != -1 || oob2 != -1 || oob3 != 0 || oob4 != 0){
        game_delete(g);
        return false;
    }
    game_play_move(g, 5, 5, S_EMPTY);
    for(uint i=0;i<DEFAULT_SIZE;i++){
        for(uint j=0;j<DEFAULT_SIZE;j++){
            if(!game_is_empty(g,i,j)){
                game_delete(g);
                return false;
            }
        }
    }
    game_delete(g);
    return true;
}

bool test_game_delete(){
    game g=game_default();
    game_set_square(g, 0, 0, S_ONE);
    game_set_square(g, 5, 0, S_ZERO);
    game_delete(g);
    if(g!=NULL){
        game_delete(g);
        return false;
    }
    game_delete(g);
    return true;
}

bool test_game_set_square(){
    game g=game_default();
    game gbis=game_default();
    game_set_square(g, 0, 0, S_IMMUTABLE_ONE);
    for(uint i=0; i<DEFAULT_SIZE; i++){
    	for(uint j=0; j<DEFAULT_SIZE; j++){
    		if(i==0&&j==0){
    			if(game_get_square(g, 0, 0)!=S_IMMUTABLE_ONE){
    				game_delete(g);
        			return false;
        		}
        	}	
    		if(game_get_square(g, i, j)!=game_get_square(gbis, i, j)){
        		game_delete(g);
        		return false;
    		}
    	}
    }
    game_set_square(g, 0, 0, S_ONE);
    for(uint i=0; i<DEFAULT_SIZE; i++){
    	for(uint j=0; j<DEFAULT_SIZE; j++){
    		if(i==0&&j==0){
    			if(game_get_square(g, 0, 0)!=S_ONE){
    				game_delete(g);
        			return false;
        		}
        	}	
    		if(game_get_square(g, i, j)!=game_get_square(gbis, i, j)){
        		game_delete(g);
        		return false;
    		}
    	}
    }
    game_set_square(g, 0, 0, S_EMPTY);
    for(uint i=0; i<DEFAULT_SIZE; i++){
    	for(uint j=0; j<DEFAULT_SIZE; j++){
    		if(i==0&&j==0){
    			if(game_get_square(g, 0, 0)!=S_EMPTY){
    				game_delete(g);
        			return false;
        		}
        	}	
    		if(game_get_square(g, i, j)!=game_get_square(gbis, i, j)){
        		game_delete(g);
        		return false;
    		}
    	}
    }
    game_set_square(g, 0, 0, S_IMMUTABLE_ZERO);
    for(uint i=0; i<DEFAULT_SIZE; i++){
    	for(uint j=0; j<DEFAULT_SIZE; j++){
    		if(i==0&&j==0){
    			if(game_get_square(g, 0, 0)!=S_IMMUTABLE_ZERO){
    				game_delete(g);
        			return false;
        		}
        	}	
    		if(game_get_square(g, i, j)!=game_get_square(gbis, i, j)){
        		game_delete(g);
        		return false;
    		}
    	}
    }
    game_set_square(g, 0, 0, S_ZERO);
    for(uint i=0; i<DEFAULT_SIZE; i++){
    	for(uint j=0; j<DEFAULT_SIZE; j++){
    		if(i==0&&j==0){
    			if(game_get_square(g, 0, 0)!=S_ZERO){
    				game_delete(g);
        			return false;
        		}
        	}	
    		if(game_get_square(g, i, j)!=game_get_square(gbis, i, j)){
        		game_delete(g);
        		return false;
    		}
    	}
    }
    game_delete(g);
    return true;
}

bool test_game_get_next_square(){
    game g=game_default();
    if(game_get_next_square(g, 0, 0, RIGHT, 1)!=S_IMMUTABLE_ONE){
        game_delete(g);
        return false;
    }
    if(game_get_next_square(g, 0, 3, LEFT, 1)!=S_IMMUTABLE_ZERO){
        game_delete(g);
        return false;
    }
    game_set_square(g, 3, 4, S_ONE);
    if(game_get_next_square(g, 5, 4, UP, 2)!=S_ONE){
        game_delete(g);
        return false;
    }
    game_set_square(g, 5, 0, S_ZERO);
    if(game_get_next_square(g, 0, 0, DOWN, 5)!=S_ZERO){
        game_delete(g);
        return false;
    }
    if(game_get_next_square(g, 0, 5, DOWN, 2)!=S_EMPTY){
        game_delete(g);
        return false;
    }
    if(game_get_next_square(g, 3, 2, UP, 6)!=-1){
        game_delete(g);
        return false;
    }
    if(game_get_next_square(g, 1, 0, DOWN, 8)!=-1){
        game_delete(g);
        return false;
    }
    if(game_get_next_square(g, 0, 0, LEFT, 3)!=-1){
        game_delete(g);
        return false;
    }
    if(game_get_next_square(g, 0, 4, RIGHT, 4)!=-1){
        game_delete(g);
        return false;
    }
    game_delete(g);
    return true;        
}


bool test_game_default(){
    game g=game_new_empty();
    game def=game_default();
    game_set_square(g, 0, 1, S_IMMUTABLE_ONE);
    game_set_square(g, 0, 2, S_IMMUTABLE_ZERO);
    game_set_square(g, 2, 1, S_IMMUTABLE_ZERO);
    game_set_square(g, 2, 4, S_IMMUTABLE_ZERO);
    game_set_square(g, 3, 1, S_IMMUTABLE_ZERO);
    game_set_square(g, 3, 2, S_IMMUTABLE_ONE);
    game_set_square(g, 4, 2, S_IMMUTABLE_ONE);
    game_set_square(g, 4, 5, S_IMMUTABLE_ZERO);
    game_set_square(g, 5, 5, S_IMMUTABLE_ZERO);
    if(game_equal(g, def)!=true){
        game_delete(g);
        game_delete(def);
        return false;
    }
    game_delete(g);
    game_delete(def);
    return true;
}

bool test_game_default_solution(){
    game g=game_new_empty();
    game def=game_default_solution();
    game_set_square(g, 0, 0, S_ZERO);
    game_set_square(g, 0, 1, S_IMMUTABLE_ONE);
    game_set_square(g, 0, 2, S_IMMUTABLE_ZERO);
    game_set_square(g, 0, 3, S_ONE);
    game_set_square(g, 0, 4, S_ZERO);
    game_set_square(g, 0, 5, S_ONE);
    game_set_square(g, 1, 0, S_ZERO);
    game_set_square(g, 1, 1, S_ONE);
    game_set_square(g, 1, 2, S_ONE);
    game_set_square(g, 1, 3, S_ZERO);
    game_set_square(g, 1, 4, S_ONE);
    game_set_square(g, 1, 5, S_ZERO);
    game_set_square(g, 2, 0, S_ONE);
    game_set_square(g, 2, 1, S_IMMUTABLE_ZERO);
    game_set_square(g, 2, 2, S_ZERO);
    game_set_square(g, 2, 3, S_ONE);
    game_set_square(g, 2, 4, S_IMMUTABLE_ZERO);
    game_set_square(g, 2, 5, S_ONE);
    game_set_square(g, 3, 0, S_ONE);
    game_set_square(g, 3, 1, S_IMMUTABLE_ZERO);
    game_set_square(g, 3, 2, S_IMMUTABLE_ONE);
    game_set_square(g, 3, 3, S_ZERO);
    game_set_square(g, 3, 4, S_ZERO);
    game_set_square(g, 3, 5, S_ONE);
    game_set_square(g, 4, 0, S_ZERO);
    game_set_square(g, 4, 1, S_ONE);
    game_set_square(g, 4, 2, S_IMMUTABLE_ONE);
    game_set_square(g, 4, 3, S_ZERO);
    game_set_square(g, 4, 4, S_ONE);
    game_set_square(g, 4, 5, S_IMMUTABLE_ZERO);
    game_set_square(g, 5, 0, S_ONE);
    game_set_square(g, 5, 1, S_ZERO);
    game_set_square(g, 5, 2, S_ZERO);
    game_set_square(g, 5, 3, S_ONE);
    game_set_square(g, 5, 4, S_ONE);
    game_set_square(g, 5, 5, S_IMMUTABLE_ZERO);
    if(game_equal(g, def)!=true){
        game_delete(g);
        game_delete(def);
        return false;
    }
    game_delete(g);
    game_delete(def);
    return true;
}

int main(int argcount, char *argv[]){
    bool test = false;
    if(argcount == 2){
        if (strcmp(argv[1], "dummy") == 0){
            if(test_dummy()){
                test = test_dummy();
            }
        }
        else if(strcmp(argv[1],"game_new_empty") == 0) {
            if(test_game_new_empty()){
                test = test_game_new_empty();
            }
        } 
        else if (strcmp(argv[1],"game_delete") == 0){
            if(test_game_delete()){
                test = test_game_delete();
            }
        }
        else if (strcmp(argv[1],"game_set_square") == 0){
            if(test_game_set_square()) {
                test = test_game_set_square();
            }
        }
        else if (strcmp(argv[1],"game_get_next_square") == 0){
            if(test_game_get_next_square()) {
                test = test_game_get_next_square();
            }
        }
        else if (strcmp(argv[1],"game_default") == 0){
            if(test_game_default()) {
                test = test_game_default();
            }
        }
        else if (strcmp(argv[1],"game_default_solution") == 0){
            if(test_game_default_solution()) {
                test = test_game_default_solution();
            }
         }
        else{
            return false;
        }
    }
    if (test == true){
        return true;
    }
    return false;
}

