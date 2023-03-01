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
