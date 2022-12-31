#include <stdbool.h>
#include <stdlib.h>

#include "game.h"
#include "queue.h"
struct game_s {
  square* tab;
  int col;
  int row;
  bool wrap;
  bool uni;
  queue* to_undo;
  queue* to_redo;
};

struct move_s {
  square s;
  int i;
  int j;
};

typedef struct game_s* game;
typedef struct move_s move_t;
