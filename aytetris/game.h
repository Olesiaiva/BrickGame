#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* colors */
#define COLOR_BLACK 0
#define COLOR_RED 1
#define COLOR_GREEN 2
#define COLOR_YELLOW 3
#define COLOR_BLUE 4
#define COLOR_MAGENTA 5
#define COLOR_CYAN 6
#define COLOR_WHITE 7


// extern char gameScreen[22][10];
extern const chtype BLOCK;
extern const char tetris[7][4][4][4];
// extern WINDOW* gameWindow;
// extern WINDOW* gameNextFigure;


enum piece_e {
  PIECE_I,
  PIECE_O,
  PIECE_L,
  PIECE_J,
  PIECE_T,
  PIECE_S,
  PIECE_Z,
  NUMBER_OF_PIECES,
};

enum rotation {
  ROTATION_NORMAL,
  ROTATION_LEFT,
  ROTATION_RIGHT,
  ROTATION_REVERSE,
};

// enum scoreCount {
//  
// };

struct coordinate {
  short x, y;
};

/* struct that represents one tetris piece in the game */
typedef struct piece {
  enum piece_e piece;
  enum rotation rotation;
  struct coordinate position;
  char gameScreen[22][10];
  WINDOW* gameWindow;
  WINDOW* gameNextFigure;
} piece;

void initWindow();
struct piece get_random_piece(void);
int check_piece_overlap(struct piece *current);
void removeCurrentPiece(struct piece *current);
void addCurrentPiece(struct piece *current);

void printGameField(struct piece *current);
void printGameNext(struct piece *current,struct piece next);
void printGameScore(int score);

void removeLine(struct piece *current, int y);
int checkLine(struct piece *current);
// int checkGame(piece current);
void newGame(int *score, piece *current, piece *next);

// move
void moveLeft(struct piece* current);
void moveRight(struct piece* current);
void moveDown(struct piece* current, struct piece* next);
void rotate(struct piece* current);


#endif /* GAME_H */