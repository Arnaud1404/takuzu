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
  printf("> action : help\n");
  printf("-press 'w <i> <j>' to put a zero/white at square (i,j)\n");
  printf("-press 'b <i> <j>' to put a one/black at square (i,j)\n");
  printf("-press 'e <i> <j>' to empty square (i,j)\n");
  printf("-press s <filename> to save current grid in a file filename.txt\n");
  printf("-press 'r' to restart \n");
  printf("-press 'q' to quit \n");
  printf("-press z to undo\n");
  printf("-press y to redo\n");
}

int main(int argc, char* argv[])
{
  game g;
  if (argc == 2) {
    g = game_load(argv[1]);  // Exemple : ./game_text default.txt, default.txt = argv[1]
  } else {
    g = game_default();
  }
  while (game_is_over(g) != true) {
    game_print(g);
    printf("> ? [h for help]\n");
    for (uint i = 0; i < 6; i++) {
      for (uint j = 0; j < 6; j++) {
        if ((game_has_error(g, i, j) != 0)) {
          printf("Error at square(%u,%u)\n", i, j);
        }
      }
    }
    char charc;
    char* filename = "save.txt";
    int retour = scanf(" %c", &charc);
    if (retour != 1) {
      help();
    } else if (charc == 'h') {
      help();
    } else if (charc == 'z') {
      printf("UNDO\n");
      game_undo(g);
    } else if (charc == 'y') {
      game_redo(g);
    } else if (charc == 'r') {
      printf("> action : restart\n");
      game_restart(g);
    } else if (charc == 'q') {
      printf("> action : quit\n");
      printf("shame\n");
      game_delete(g);
      return EXIT_SUCCESS;
    } else if (charc == 's') {
      if (filename == NULL) {
        game_delete(g);
        exit(EXIT_FAILURE);
      }
      game_save(g, filename);
      printf("Game saved\n");

    } else if (charc == 'w' || charc == 'b' || charc == 'e' || charc == 'z' || charc == 'y') {
      uint it, jt;
      square jouer;
      int retourbis = scanf("%u %u", &it, &jt);
      if (retourbis != 2) {
        help();
      } else if (charc == 'w') {
        jouer = S_ZERO;
        if (game_check_move(g, it, jt, jouer) == true) {
          printf("> action : play move '%c' into square (%u,%u)\n", charc, it, jt);
          game_play_move(g, it, jt, jouer);
        }
      } else if (charc == 'b') {
        jouer = S_ONE;
        if (game_check_move(g, it, jt, jouer) == true) {
          printf("> action : play move '%c' into square (%u,%u)\n", charc, it, jt);
          game_play_move(g, it, jt, jouer);
        }
      } else if (charc == 'e') {
        jouer = S_EMPTY;
        if (game_check_move(g, it, jt, jouer) == true) {
          game_play_move(g, it, jt, jouer);
        }
      }
    }
  }
  game_print(g);
  printf("congratulation\n");
  game_delete(g);
  return EXIT_SUCCESS;
}