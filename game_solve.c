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
  if (argc == 3) {
    char* filename = argv[3];
    g = game_load(argv[2]);
    if (strcmp(argv[1], "-s") == 0) {
      bool ret = game_solve(g);
      if (!ret) {
        return EXIT_FAILURE;
      }

      game_save(g, filename);
    }

    if (strcmp(argv[1], "-c") == 0) {
      int n = game_nb_solutions(g);  // 0 si aucune solution
      FILE* file_game = fopen(filename, "w");
      if (file_game == NULL) {
        exit(EXIT_FAILURE);
      }
      fprintf(file_game, "%d\n", n);
    }
  }

  return EXIT_SUCCESS;
}
