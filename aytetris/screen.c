#include "game.h"

void removeCurrentPiece(struct piece *current) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (tetris[current->piece][current->rotation][y][x])
        current->gameScreen[current->position.y - y][current->position.x + x] = 0;
    }
  }
}

void addCurrentPiece(struct piece *current) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (tetris[current->piece][current->rotation][y][x])
        current->gameScreen[current->position.y - y][current->position.x + x] =
            current->piece + 1;
    }
  }
}

void printGameField(struct piece *current) {
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

void printGameNext(struct piece *current, struct piece next) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (tetris[next.piece][next.rotation][3 - y][x]) {
        wattron(current->gameNextFigure, COLOR_PAIR(next.piece + 1));
        mvwaddch(current->gameNextFigure, y + 2, x * 2 + 4, BLOCK);
        mvwaddch(current->gameNextFigure, y + 2, x * 2 + 5, BLOCK);
        wattroff(current->gameNextFigure, COLOR_PAIR(next.piece + 1));
      } else {
        mvwaddch(current->gameNextFigure, y + 2, x * 2 + 4, ' ');
        mvwaddch(current->gameNextFigure, y + 2, x * 2 + 5, ' ');
      }
    }
  }
  wrefresh(current->gameNextFigure);
}

void printGameScore(int score) {
  mvprintw(15, 35,"Score %d", score);
  mvprintw(16, 35,"Level %d", score / 100);
}

void removeLine(struct piece *current,int y) {
    for (int h = y; h > 2; h--) {
      for (int x = 0; x < 10; x++) {
        current->gameScreen[h][x] = current->gameScreen[h - 1][x];
      }
    }
}

int checkLine(struct piece *current) {
  int x, score = 0;
  for (int y = 0; y < 22; y++) {
    for (x = 0; x < 10 && current->gameScreen[y][x]; x++);
    if (x == 10) {
      removeLine(current,y);
      score++;
    }
  }
  return score * 20 + score / 2 * 100;
}

// int checkGame(piece current) {
  
//   int status = 1;
//   if (current->gameScreen[4][4]) {
//     mvprintw(13, 15, "Game over!!!");
//     status = 0;
//   }
//   return status;
// }