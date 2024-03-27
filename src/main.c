#include "game.h"
  
  const chtype BLOCK = ' ' | A_REVERSE;

int main() {
  struct piece current = get_random_piece();
  struct piece next = get_random_piece();
  initWindow(&current);
  current.gameWindow = newwin(22 + 2, 10 * 2 + 2, 2, 10);
  refresh();
  int flag = 1;


  while (flag)  //
    {
    wclear(current.gameWindow);
    wborder(current.gameWindow, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK);

    switch (getch()) {
      case KEY_UP:
      case 'w':
        rotate(&current);
        break;
      case KEY_LEFT:
      case 'a':
        moveLeft(&current);
        break;
      case KEY_DOWN:
      case 's':
        moveDown(&current, &next);
        break;
      case KEY_RIGHT:
      case 'd':
        moveRight(&current);
        break;
      case 'q':
      flag =  0;
        // return 0;
        break;
    }

    addCurrentPiece(&current);

    printGameField(&current);

    moveDown(&current, &next);

    checkLine(&current);

    wrefresh(current.gameWindow);
  }  //

  delwin(current.gameWindow);
  endwin();
  return 0;
}