
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>
#include <math.h>
#define KY 1
#define KX 2
#define MK 7
void draw(int (*game_field)[12],int (*data)[21]);
void set_game_field(int (*game_field)[12]);
void get_data(int (*game_field)[12],int (*data)[21]);
void generate_figure(const uint8_t (*FIGURES)[4][2],int (*current_figure)[2],int* fig_num);
void figure_to_game_field(const uint8_t (*FIGURES)[4][2],int* fig_num,int (*game_field)[12],int (*current_figure)[2]);

void set_game_field(int (*game_field)[12]){
    for (int i=0; i<20; i++){
        for (int j=1; j<11; j++){
            game_field[i][j] = 0;
        }
    }
    for (int j=1; j<11; j++){ game_field[20][j] = 7; }
    for (int m=1; m<11; m++){ game_field[0][m] = 7; }
    for (int i=0; i<21; i++){ 
      game_field[i][0] = 7; 
      game_field[i][11] = 7; 
    }
}


void get_data(int (*game_field)[12],int (*data)[21]){

    for (int i=0; i<21; i++){
        for (int j=0; j<12; j++){
            data[i][j] = game_field[i][j];
        }
    }

    // for (int i=0; i<4; i++){
    //     data[current_figure[i][1]][current_figure[i][0]] = fig_num[1] + 1;
    // }

    // for (int i=0; i<4; i++){
    //     for (int j=0; j<4; j++){
    //         data[9 + i][14 + j] = 0;
    //     }
    // }

    // for (int i=0; i<4; i++){
    //     data[ FIGURES[fig_num[0]][i][1] + 9][ FIGURES[fig_num[0]][i][0] + 14] = fig_num[0] + 1;
    // }
}
void generate_figure(const uint8_t (*FIGURES)[4][2],int (*current_figure)[2],int* fig_num){
    fig_num[1] = fig_num[0]; 
    fig_num[0] = rand()%7; //rand number for a figure
    for (int i=0; i<4; i++){
        for (int j =0; j<2; j++){
            current_figure[i][j] = FIGURES[fig_num[1]][i][j];
        }
        current_figure[i][0] += 5;
        current_figure[i][1] -= 1;
    }
}
void draw(int (*game_field)[12],int (*data)[21]){
    clear();
    get_data(game_field,data);
    for (int i = 0; i < 21; i++){
        for(int j = 0; j < 12; j++){


            for(int kx = 0; kx < KX; kx++){
            for(int ky = 0; ky < KY; ky++){
            if (game_field[i][j] == 7) {
                mvaddch(i * KY + ky, j * KX + kx, ACS_CKBOARD);
            } else if (game_field[i][j] == 0) {
                mvaddch(i * KY + ky, j * KX + kx, ' ' );
            }
            }
            }
                // for(int kx = 0; kx < KX; kx++){
                //     for(int ky = 0; ky < KY; ky++){
                //         mvaddch(i * KY + ky, j * KX + kx , ACS_CKBOARD); // +ky +kx
                //     }
                // }
            

          
        }
    }
    refresh();
}
void figure_to_game_field(const uint8_t (*FIGURES)[4][2],int* fig_num,int (*game_field)[12],int (*current_figure)[2]){
    for (int i=0; i<4; i++){
        game_field[current_figure[i][1]][current_figure[i][0]] = fig_num[1] + 1;
    }
}

int main() {
const uint8_t FIGURES[7][4][2] = {
//   _______
//  |_|_|_|_|
//
    {
        {0, 0},{1, 0},{2, 0},{3, 0}
    },
//   ___
//  |_|_|
//  |_|_|
//
    {
        {0, 0},{1, 0},{1, 1},{0, 1}
    },
//   _____
//  |_|_|_|
//      |_|
//
    {
        {0, 0},{1, 0},{2, 0},{2, 1}
    },
//   _____
//  |_|_|_|
//  |_|
//
    {
        {0, 1},{1, 1},{2, 1},{2, 0}
    },
//     ___
//   _|_|_|
//  |_|_|
//
    {
        {0, 0},{0, 1},{1, 1},{1, 2}
    },
//   ___
//  |_|_|_
//    |_|_|
//
    {
        {0, 0},{1, 0},{1, 1},{2, 1}
    },
//   _____
//  |_|_|_|
//    |_|
//
    {
        {0, 0},{1, 0},{2, 0},{1, 1}
    }
};
    int game_field[21][12]; 
    int current_figure[4][2];
    int fig_num[2], rotation_flag;
    int data[21][21];
    int key = 0;
    initscr(); 
    curs_set(0); 
    start_color(); 
      noecho();
           init_pair(1, COLOR_RED, COLOR_BLACK);
    timeout(-1);
    getch();
   

while((key  = getch()) != 27){
 
  // if(key == KEY_UP) rotate();
  // else if(key == KEY_DOWN) move_down();
  // else if(key == KEY_LEFT) move_left();
  // else if(key == KEY_RIGHT) move_right();
  set_game_field(game_field);
  // generate_figure(FIGURES,current_figure,fig_num);
  draw(game_field,data);
  // figure_to_game_field(FIGURES,fig_num,game_field,current_figure);

}
endwin();
    return 0;
}