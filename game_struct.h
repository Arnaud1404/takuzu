#include "queue.h"
#include<stdbool.h>
#include<stdlib.h>
#include "game.h"
struct game_s {
  square* tab;
  int col;
  int row;
  bool wrap;
  bool uni;
  queue* to_undo;
  queue* to_redo;
};

typedef struct game_s* game;