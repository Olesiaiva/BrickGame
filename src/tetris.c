#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>
#include <math.h>
enum piece_e {
  PIECE_I,
  PIECE_O,
  PIECE_L,
  PIECE_J,
  PIECE_T,
  PIECE_S,
  PIECE_Z,
};

enum rotation {
  ROTATION_NORMAL,
  ROTATION_LEFT,
  ROTATION_RIGHT,
  ROTATION_REVERSE,
};

struct coordinate {
  short x, y;
};

/* struct that represents one tetris piece in the game */
typedef struct figure {
  enum piece_e piece;
  enum rotation rotation;
  struct coordinate position;
}figure ;
void set_game_field( int  (*game_field)[10], const int (*pieces)[4][4][4], figure *current_figure);
void move_left(figure *current_figure);
void move_right(figure *current_figure);
void remove_current_figure(int  (*game_field)[10], figure *current_figure);
void add_current_figure(int  (*game_field)[10], figure *current_figure, const int (*pieces)[4][4][4]);
void rotate(figure *current_figure);
int main() {
    figure current_figure;
    srand(time(0));
    const int pieces[7][4][4][4] = {
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

    int game_field[22][10];
    set_game_field(game_field, pieces, &current_figure);

    initscr(); // Инициализация экрана ncurses
    cbreak(); // Включение режима прямого ввода символов, без буферизации
    noecho(); // Отключение эхо-режима (не отображать ввод пользователя)
    curs_set(0); // Скрыть курсор
    timeout(100);
    keypad(stdscr, TRUE); // Включить клавиатуру
    int ch;
    int key;
    WINDOW *field = newwin(24, 24, 1, 1); // Создание окна 'field' размером 22 строк на 12 столбца



    while ((ch = getch()) != 113 ){    //?????
    wclear(field);
   
        mvwhline(field, 1, 0, ACS_CKBOARD, 24); // Горизонтальная линия верх 
        mvwhline(field, 22, 0, ACS_CKBOARD, 24); // Горизонтальная линия верх 

    for(int i = 2; i < 22;i++){
        mvwvline(field, i, 1, ACS_CKBOARD, 1); // Вертикальная линия линия ACS_VLINE
        mvwvline(field, i, 0, ACS_CKBOARD, 1); // Вертикальная линия линия ACS_VLINE
    }
     for(int i = 2; i< 22;i++){
        mvwvline(field, i, 22, ACS_CKBOARD, 1); // Вертикальная линия линия ACS_VLINE
        mvwvline(field, i , 23, ACS_CKBOARD, 1); // Вертикальная линия линия ACS_VLINE
    }

    wrefresh(field);
    refresh();
    for(int i = 0; i < 20 ;i++){
        for(int j = 0; j< 10; j++){
            if(game_field[i][j]){
        mvwaddch(field, i + 1, j * 2 + 2 , ' ' | A_REVERSE); 
        mvwaddch(field, i + 1, j * 2 + 3, ' ' | A_REVERSE);
            }

        }
    }
      
   
    if(ch == KEY_DOWN){
      
    }
    else if(ch == KEY_LEFT){
    remove_current_figure(game_field, &current_figure);
     move_left(&current_figure);
    }
    else if(ch == KEY_RIGHT){
        remove_current_figure(game_field, &current_figure);
        move_right(&current_figure);
    }
    else if(ch == KEY_UP){
      remove_current_figure(game_field, &current_figure);
      rotate(&current_figure);
    }
    
    add_current_figure(game_field, &current_figure, pieces);
        // mvwaddch(field, y, x , ' ' | A_REVERSE); 
        // mvwaddch(field, y, x + 1, ' ' | A_REVERSE);

        //moveDown
        // y+=1;
        // mvwaddch(field, y, x, ' ');
        //??
        refresh();
        wrefresh(field);
    
    } //>???




    
    delwin(field); // Удаление окна 'field'
    endwin(); // Завершение работы с ncurses

    return 0;


}

void set_game_field( int  (*game_field)[10], const int (*pieces)[4][4][4],  figure *current_figure){
  
    int rand_figure = rand() % 7;
      for(int i = 0 ; i < 22; i++){
        for(int j = 0; j < 10; j++){
         game_field[i][j] = 0;
        }
     
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j< 4;j++){
            game_field[i + 1][j + 5] = pieces[0][0][i][j];
        }
    }
    current_figure->piece = rand_figure;
    current_figure->rotation = 0;
    current_figure->position.x = 5;
    current_figure->position.y = 1;

}

void move_left(figure *current_figure){
    current_figure->position.x -= 1;
}
void move_right(figure *current_figure){
    current_figure->position.x += 1;
}
void remove_current_figure(int  (*game_field)[10], figure *current_figure){
    for(int i = 0; i< 4; i++){
        for (int j = 0; j< 4; j++){
            game_field[current_figure->position.y + i][current_figure->position.x + j] = 0;
        }
    }
}

void  add_current_figure(int  (*game_field)[10], figure *current_figure, const int (*pieces)[4][4][4]){
        for(int i = 0; i< 4; i++){
        for (int j = 0; j< 4; j++){
            game_field[current_figure->position.y + i][current_figure->position.x + j] = pieces[current_figure->piece][current_figure->rotation][i][j];
        }
    }
}
void rotate(figure *current_figure){
    if( current_figure->rotation == 3){
    current_figure->rotation = 0;

    }
    else{
    current_figure->rotation += 1;

    }
}