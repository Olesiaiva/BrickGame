#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>
#include <math.h>
void set_game_field( int  (*game_field)[12]);
int main() {
  int game_field[22][12];
    set_game_field(game_field);
    initscr(); // Инициализация экрана ncurses
    cbreak(); // Включение режима прямого ввода символов, без буферизации
    noecho(); // Отключение эхо-режима (не отображать ввод пользователя)
    curs_set(0); // Скрыть курсор
    keypad(stdscr, TRUE); // Включить клавиатуру
    WINDOW *field = newwin(22, 12 * 2, 0, 0); // Создание окна 'field' размером 12 строк на 22 столбца
  //   box(field, 0, 0); // Отрисовка рамки вокруг окна
  // refresh();
    // // Отрисовка прямых черточек внутри поля
    // for (int i = 1; i < 12; i++) {
    //     mvwhline(field, i, 1, ACS_VLINE, 20); // Вертикальная линия
    // }
    // for (int i = 1; i < 20; i += 2) {
    //     mvwvline(field, 1, i, ACS_HLINE, 10); // Горизонтальная линия
    // }
       for (int i = 0; i < 22; i++){
        for(int j = 0; j < 12; j++){
                if(game_field[i][j]){
                mvwaddch(field,i + 1, j * 2 + 1, ACS_VLINE);
                }else{
                mvwaddch(field, i + 1, j * 2 + 1, ' ' );
                }
        }
   
    } 
    // Отображение изменений
    // wrefresh(field);

    int ch;
    int x = 10; // Начальные координаты символа '@'
    int y = 5;

    // Отображение символа '@' и перемещение
    mvwaddch(field, y, x, '@');
    refresh();
    wrefresh(field);

    // Цикл ожидания перемещения символа '@'
    while ((ch = getch()) != 'q') {
        // Обрабатываем нажатия клавиш для перемещения символа
        switch(ch) {
            case KEY_UP:
                mvwaddch(field, y, x, ' '); // Стираем предыдущее положение '@'
                y -= 1;
                break;
            case KEY_DOWN:
                mvwaddch(field, y, x, ' '); // Стираем предыдущее положение '@'
                y += 1;
                break;
            case KEY_LEFT:
                mvwaddch(field, y, x, ' '); // Стираем предыдущее положение '@'
                x -= 2;
                break;
            case KEY_RIGHT:
                mvwaddch(field, y, x, ' '); // Стираем предыдущее положение '@'
                x += 2;
                break;
            default:
                break;
        }

        mvwaddch(field, y, x, '@'); // Отрисовка символа '@' на новых координатах
        refresh();
        wrefresh(field);
    }

    delwin(field); // Удаление окна 'field'
    endwin(); // Завершение работы с ncurses

    return 0;


}

void set_game_field( int  (*game_field)[12]){
    for(int i = 0; i < 22; i++){
        game_field[i][0] = 1;
        game_field[i][11] = 1;
    } 
    for(int j = 1; j < 11; j++) game_field[0][j] = 1;
    for(int m = 1; m < 11; m++) game_field[21][m] = 1;

    for(int g = 1; g < 21; g++){
        for(int y = 1; y < 11; y++){
            game_field[g][y] = 0;
        }
    }
}