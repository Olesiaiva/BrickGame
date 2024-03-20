#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};
int currentPiece[4][4];
int currentX, currentY;
int score = 0;
int gameOver = 0;

void createNewPiece() {
    static int pieces[7][4][4] = {
        {{1, 1, 1, 1},
         {0, 0, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},

        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},

        {{1, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},

        {{0, 1, 1, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},

        {{1, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},

        {{0, 0, 1, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},

        {{1, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}
    };

    int randomPiece = rand() % 7;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            currentPiece[i][j] = pieces[randomPiece][i][j];
        }
    }

    currentX = BOARD_WIDTH / 2 - 2;
    currentY = 0;
}

void drawBoard() {
    clear();
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] || (i >= currentY && i < currentY + 4 && j >= currentX && j < currentX + 4 && currentPiece[i - currentY][j - currentX])) {
                attron(COLOR_PAIR(1));
                mvprintw(i, j * 2, "[]");
                attroff(COLOR_PAIR(1));
            } else {
                mvprintw(i, j * 2, "  ");
            }
        }
    }
    mvprintw(BOARD_HEIGHT + 2, 2, "Score: %d", score);
    refresh();
}

int checkCollision(int newX, int newY) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentPiece[i][j] && (newY + i >= BOARD_HEIGHT || newX + j < 0 || newX + j >= BOARD_WIDTH || board[newY + i][newX + j])) {
                return 1;
            }
        }
    }
    return 0;
}

void mergePiece() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentPiece[i][j]) {
                board[currentY + i][currentX + j] = 1;
            }
        }
    }
}

void checkLines() {
    for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
        int lineFull = 1;
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (!board[i][j]) {
                lineFull = 0;
                break;
            }
        }
        if (lineFull) {
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }
            for (int j = 0; j < BOARD_WIDTH; j++) {
                board[0][j] = 0;
            }
            score += 100;
            i++; // Recheck the same row as it has been shifted down
        }
    }
}
void movePiece(int deltaX, int deltaY) {
    if (!checkCollision(currentX + deltaX, currentY + deltaY)) {
        currentX += deltaX;
        currentY += deltaY;
    }
}

void rotatePiece() {
    int tempPiece[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tempPiece[i][j] = currentPiece[j][3 - i];
        }
    }

    if (!checkCollision(currentX, currentY + 1)) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                currentPiece[i][j] = tempPiece[i][j];
            }
        }
    }
}



void gameLoop() {
    int delay = 500;
    while (!gameOver) {
        createNewPiece();
        while (!checkCollision(currentX, currentY + 1)) {
            drawBoard();
            usleep(delay * 1000);
            movePiece(0, 1);
        }
        mergePiece();
        checkLines();
        drawBoard();

        if (currentY == 0) {
            gameOver = 1;
        }
    }
}

int main() {
    srand(time(NULL));
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    drawBoard();
    gameLoop();
    mvprintw(BOARD_HEIGHT / 2, BOARD_WIDTH / 2 - 5, "GAME OVER");
    mvprintw(BOARD_HEIGHT / 2 + 1, BOARD_WIDTH / 2 - 7, "Final Score: %d", score);
    refresh();
    getch();
    endwin();
    return 0;
}