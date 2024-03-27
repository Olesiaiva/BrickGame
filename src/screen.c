#include "game.h"

void removeCurrentPiece(struct piece* current) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (tetris[current->piece][current->rotation][y][x])
        current->gameScreen[current->position.y - y][current->position.x + x] = 0;
    }
  }
}

void addCurrentPiece(struct piece* current) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (tetris[current->piece][current->rotation][y][x])
        current->gameScreen[current->position.y - y][current->position.x + x] =
            current->piece + 1;
    }
  }
}

void printGameField(struct piece* current) {
  for (int y = 0; y < 22; y++) {
    for (int x = 0; x < 10; x++) {
      if (current->gameScreen[y][x]) {
        wattron(current->gameWindow, COLOR_PAIR(current->gameScreen[y][x]));
        mvwaddch(current->gameWindow, y + 1, x * 2 + 1, BLOCK);
        mvwaddch(current->gameWindow, y + 1, x * 2 + 2, BLOCK);
        wattroff(current->gameWindow, COLOR_PAIR(current->gameScreen[y][x]));
      } else {
        mvwaddch(current->gameWindow, y + 1, x * 2 + 1, ' ');
        mvwaddch(current->gameWindow, y + 1, x * 2 + 2, ' ');
      }
    }
  }
  wrefresh(current->gameWindow);
}

void removeLine(struct piece* current,int y) {
    for (int h = y; h > 2; h--) {
      for (int x = 0; x < 10; x++) {
        current->gameScreen[h][x] = current->gameScreen[h - 1][x];
      }
    }
}

void checkLine(struct piece* current) {
  int x;
  for (int y = 0; y < 22; y++) {
    for (x = 0; x < 10 && current->gameScreen[y][x]; x++);
    if (x == 10)
      removeLine(current,y);
  }
}