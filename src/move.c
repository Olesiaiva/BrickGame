#include "game.h"

void moveLeft(piece* current) {
  current->position.x -= 1;
  if (check_piece_overlap(current)) {
    removeCurrentPiece(current);
    wrefresh(gameWindow);
  } else {
    current->position.x += 1;
  }
}

void moveRight(piece* current) {
  current->position.x += 1;
  if (check_piece_overlap(current)) {
    removeCurrentPiece(current);
    wrefresh(gameWindow);
  } else {
    current->position.x -= 1;
  }
}

void moveDown(piece* current, piece* next) {
    removeCurrentPiece(current);
    current->position.y += 1;
  if (!check_piece_overlap(current)) {
    current->position.y -= 1;
    addCurrentPiece(current);
    *current = *next;
    *next = get_random_piece();
  }
    wrefresh(gameWindow);

}

void rotate(piece* current) {
  if (current->rotation == 3) {
    current->rotation = 0;
  } else {
    current->rotation += 1;
  }

  if (check_piece_overlap(current)) {
    removeCurrentPiece(current);
    wrefresh(gameWindow);
  } else {
    current->rotation -= 1;
  }
}