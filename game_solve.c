#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"
#define DEFAULT_SIZE 6

void help(void)
{
  printf("> action : help\n");
  printf("-press 's' to search the solution of the game\n");
  printf("-press 'c' to count the number of solution and save it\n");
}

int main(int argc, char* argv[])
{
  game g;
  if (argc < 3) {
    return EXIT_FAILURE;
  }
  bool tosave = argc == 4;
  char* filename = argv[2];
  g = game_load(filename);
  if (strcmp(argv[1], "-s") == 0) {
    bool ret = game_solve(g);
    if (!ret) {
      return EXIT_FAILURE;
    }
    if(tosave){
      char* filename2 = argv[3];
      game_save(g, filename2);
    }
    else game_print(g);  
  }

  if (strcmp(argv[1], "-c") == 0) {
    uint n = game_nb_solutions(g);  // 0 si aucune solution
    if(tosave){
      FILE* text = fopen(filename,"w");
      char tab [5];
      sprintf(tab,"%u",n);
      fputs(tab,text);
    }
    else
      printf("%d\n", n);
  }



  return EXIT_SUCCESS;
}
