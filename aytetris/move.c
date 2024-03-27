#include "game.h"

void moveLeft(piece* current) {
  current->position.x -= 1;
  if (check_piece_overlap(current)) {
    removeCurrentPiece(current);
    wrefresh(current->gameWindow);
  } else {
    current->position.x += 1;
  }
}

void moveRight(piece* current) {
  current->position.x += 1;
  if (check_piece_overlap(current)) {
    removeCurrentPiece(current);
    wrefresh(current->gameWindow);
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
    current->piece = next->piece;
    current->rotation = next->rotation;
    current->position = next->position;
    *next = get_random_piece();
  }
    wrefresh(current->gameWindow);

}

void rotate(piece* current) {
  if (current->rotation == 3) {
    current->rotation = 0;
  } else {
    current->rotation += 1;
  }

  if (check_piece_overlap(current)) {
    removeCurrentPiece(current);
    wrefresh(current->gameWindow);
  } else {
    current->rotation -= 1;
  }
}