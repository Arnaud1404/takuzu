#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"
#define DEFAULT_SIZE 6

void help(void)
{
  printf("> action : help\n") ;
  printf("-press 's' to search the solution of the game\n");
  printf("-press 'c' to count the number of solution and save it\n");
}


int main(int argc, char* argv[])
{
  game g;
  if (argc == 3) {
    g = game_load(argv[1]);
    game_solve(g);
    game_print(g);
    
    char* c = argv[2];
    game_save(g,c);
  }
  return EXIT_SUCCESS;
}