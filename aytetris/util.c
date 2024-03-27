#include "game.h"

const char tetris[7][4][4][4] = {
    {
        /* I */
        {{1}, {1}, {1}, {1}},
        {{1, 1, 1, 1}},
        {{1}, {1}, {1}, {1}},
        {{1, 1, 1, 1}},
    },
    {
        /* O */
        {{1, 1}, {1, 1}, {0}, {0}},
        {{1, 1}, {1, 1}, {0}, {0}},
        {{1, 1}, {1, 1}, {0}, {0}},
        {{1, 1}, {1, 1}, {0}, {0}},
    },
    {
        /* L */
        {{1, 1}, {1}, {1}, {0}},
        {{1, 1, 1}, {0, 0, 1}, {0}, {0}},
        {{0, 1}, {0, 1}, {1, 1}, {0}},
        {{1}, {1, 1, 1}, {0}, {0}},
    },
    {
        /* J */
        {{1, 1}, {0, 1}, {0, 1}, {0}},
        {{0, 0, 1}, {1, 1, 1}, {0}, {0}},
        {{1}, {1}, {1, 1}, {0}},
        {{1, 1, 1}, {1}, {0}, {0}},
    },
    {
        /* T */
        {{0, 1}, {1, 1, 1}, {0}, {0}},
        {{1}, {1, 1}, {1}, {0}},
        {{1, 1, 1}, {0, 1}, {0}, {0}},
        {{0, 1}, {1, 1}, {0, 1}, {0}},
    },
    {
        /* S */
        {{0, 1}, {1, 1}, {1}, {0}},
        {{1, 1}, {0, 1, 1}, {0}, {0}},
        {{0, 1}, {1, 1}, {1}, {0}},
        {{1, 1}, {0, 1, 1}, {0}, {0}},
    },
    {
        /* Z */
        {{1}, {1, 1}, {0, 1}, {0}},
        {{0, 1, 1}, {1, 1}, {0}, {0}},
        {{1}, {1, 1}, {0, 1}, {0}},
        {{0, 1, 1}, {1, 1}, {0}, {0}},
    },
};

void initWindow() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, 1);
  curs_set(0);
  timeout(300);  // speed

  // usleep(100000);
  srand(time(0));

  use_default_colors();
  start_color();
  init_pair(1, COLOR_CYAN, -1);
  init_pair(2, COLOR_YELLOW, -1);
  init_pair(3, 203, -1);
  init_pair(4, COLOR_BLUE, -1);
  init_pair(5, COLOR_MAGENTA, -1);
  init_pair(6, COLOR_GREEN, -1);
  init_pair(7, COLOR_RED, -1);
}

piece get_random_piece(void) {
  piece p = {
      .piece = rand() % NUMBER_OF_PIECES,
      .rotation = ROTATION_NORMAL,
      .position =
          {
              .x = 4,
              .y = 3,
          },
  };

  return p;
}

int check_piece_overlap(struct piece *current) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (tetris[current->piece][current->rotation][y][x] && (
        (current->position.y - y > 21) || (current->position.y - y < 0) ||
        (current->position.x + x < 0) || (current->position.x + x >= 10)
        || (current->gameScreen[current->position.y - y][current->position.x + x])
        )
        )
        return 0;
    }
  }
  return 1;
}

void newGame(int *score, piece *current, piece *next) {
  memset(current->gameScreen, 0, sizeof(current->gameScreen));
  *current = get_random_piece();
  *next = get_random_piece();
  *score = 0;
}