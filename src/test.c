#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

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
typedef enum direction { LEFT, RIGHT, DOWN } direction;
struct coordinate {
  short x[4], y[4], old_x[4], old_y[4], init_x, init_y, init_old_x, init_old_y;
};

/* struct that represents one tetris piece in the game */
typedef struct figure {
  enum piece_e piece;
  enum rotation rotation;
  enum rotation old_rotation;
  struct coordinate position;
} figure;
void set_game_field(int (*game_field)[10], const int (*pieces)[4][4][4],
                    figure *current_figure);
void move_left(int (*game_field)[10], figure *current_figure,
               const int (*pieces)[4][4][4]);
void move_right(int (*game_field)[10], figure *current_figure,
                const int (*pieces)[4][4][4]);
void move_down(int (*game_field)[10], figure *current_figure,
               const int (*pieces)[4][4][4]);
void remove_current_figure(int (*game_field)[10], figure *current_figure,
                           const int (*pieces)[4][4][4]);
void add_current_figure(int (*game_field)[10], figure *current_figure,
                        const int (*pieces)[4][4][4]);
void rotate(int (*game_field)[10], figure *current_figure,
            const int (*pieces)[4][4][4]);
int block_can_move(int (*game_field)[10], figure *current_figure,
                   const int (*pieces)[4][4][4]);
void position_x_minus(figure *current_figure);
void position_x_plus(figure *current_figure);
void position_y_plus(figure *current_figure);
void position_y_minus(figure *current_figure);
void eq_old_y_new_y(figure *current_figure);
void eq_old_x_new_x(figure *current_figure);
void  add_tmp_game_field(int (*tmp_game_field)[10],figure * tmp_current_figure, const int (*pieces)[4][4][4]);
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
  int t  = 3;
  set_game_field(game_field, pieces, &current_figure);
  while (t--)
 
  {
    // printf("%d %d\n", current_figure.position.init_x, current_figure.position.init_y);

  int ch;
  int key;

 


    // for (int i = 0; i < 22; i++) {
    //   for (int j = 0; j < 10; j++) {
       
    // printf("%d", game_field[i][j]);
        
    
    //   }

    //   printf("\n");

    // }
    //   printf("\n");
      
  // for(int i = 0; i < 4; i++){
  //   printf("%d %d\n", current_figure.position.y[i], current_figure.position.x[i]);
  // }
  //  printf("\n");

      // move_down(game_field, &current_figure, pieces);
       rotate(game_field, &current_figure, pieces);
    //       for(int i = 0; i < 4; i++){ 
    //   printf("%d %d \n", current_figure.position.y[i], current_figure.position.x[i]);
    // }
    // printf("\n");
  
   add_current_figure(game_field, &current_figure, pieces);
    // for (int i = 0; i < 22; i++) {
    //   for (int j = 0; j < 10; j++) {
       
    // printf("%d", game_field[i][j]);
        
    
    //   }

    //   printf("\n");

    // }
    //   printf("\n");
    // for(int i = 0; i < 4; i++){ 
    //   printf("dva %d %d\n", current_figure.position.y[i], current_figure.position.x[i]);
    // }
    // printf("\n");


  
      // move_left(game_field, &current_figure, pieces);

  
      // move_right(game_field, &current_figure, pieces);
  
      // rotate(game_field, &current_figure, pieces);
    

   

        // Завершение работы с ncurses
}

  return 0;
}

void set_game_field(int (*game_field)[10], const int (*pieces)[4][4][4],
                    figure *current_figure) {
  int rand_figure = rand() % 7;
  for (int i = 0; i < 22; i++) {
    for (int j = 0; j < 10; j++) {
      game_field[i][j] = 0;
    }
  }
int k  = -1;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game_field[i + 1][j + 5] = pieces[0][0][i][j];
      if (game_field[i + 1][j + 5] == 1) {
        ++k;
        current_figure->position.y[k] = i + 1;
        current_figure->position.x[k] = j + 5;
        current_figure->position.old_y[k] = i + 1;
        current_figure->position.old_x[k] = j + 5;
      
      }
    }
  }
  current_figure->piece = 0;
  current_figure->rotation = 0;
  current_figure->old_rotation = 0;
  current_figure->position.init_x = 5;
  current_figure->position.init_y = 1;
  current_figure->position.init_old_y = 1;
  current_figure->position.init_old_x = 5;
}

void move_left(int (*game_field)[10], figure *current_figure,
               const int (*pieces)[4][4][4]) {
  position_x_minus(current_figure);
  if (block_can_move(game_field, current_figure, pieces)) {
    remove_current_figure(game_field, current_figure, pieces);
    eq_old_x_new_x(current_figure);

  } else {
    position_x_plus(current_figure);
  }
}
void move_right(int (*game_field)[10], figure *current_figure,
                const int (*pieces)[4][4][4]) {
  position_x_plus(current_figure);
  if (block_can_move(game_field, current_figure, pieces)) {
    remove_current_figure(game_field, current_figure, pieces);
    eq_old_x_new_x(current_figure);
  } else {
    position_x_minus(current_figure);
  }
}
void remove_current_figure(int (*game_field)[10], figure *current_figure,
                           const int (*pieces)[4][4][4]) {

  for (int i = 0; i < 4; i++) {
      game_field[current_figure->position.old_y[i]][current_figure->position.old_x[i]] = 0;
  }
 
}

void add_current_figure(int (*game_field)[10], figure *current_figure,
                        const int (*pieces)[4][4][4]) {
 
  int k = -1;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
        if(pieces[current_figure->piece][current_figure->rotation][i][j] == 1){
      game_field[current_figure->position.init_y + i][current_figure->position.init_x + j] = pieces[current_figure->piece][current_figure->rotation][i][j];
          ++k;
          current_figure->position.old_y[k] = current_figure->position.init_y + i;
          current_figure->position.old_x[k] = current_figure->position.init_x + j;
          current_figure->position.y[k] = current_figure->position.init_y  + i;
          current_figure->position.x[k] = current_figure->position.init_x  + j;

        }
 

  
  }

  }

}
void rotate(int (*game_field)[10], figure *current_figure,
            const int (*pieces)[4][4][4]) {
  if (current_figure->rotation == 3) {
    current_figure->rotation = 0;
  } else {
    current_figure->rotation += 1;
  }
  figure tmp_current_figure = *current_figure;
  int tmp_game_field[22][10] = game_field;

  add_tmp_game_field(tmp_game_field, tmp_current_figure, pieces);
  if (block_can_move(game_field, current_figure, pieces)) {
    remove_current_figure(game_field, current_figure, pieces);
    current_figure->old_rotation = current_figure->rotation;

  } else {
    current_figure->rotation = current_figure->old_rotation;
  }
}
int block_can_move(int (*game_field)[10], figure *current_figure,
                   const int (*pieces)[4][4][4]) {
  int flag = 1;
  int k = -1;
 
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if ((pieces[current_figure->piece][current_figure->rotation][i][j]) == 1){
        ++k;
             if((current_figure->position.x[k] >= 10) ||
          (current_figure->position.x[k]  < 0) ||
          (current_figure->position.y[k] >= 22)) {
            
        flag = 0;
          }
      }
     
    }
  
  }

  return flag;
}

void move_down(int (*game_field)[10], figure *current_figure,
               const int (*pieces)[4][4][4]) {
  position_y_plus(current_figure);
  if (block_can_move(game_field, current_figure, pieces)) {
    remove_current_figure(game_field, current_figure, pieces);
    eq_old_y_new_y(current_figure);
  } else {
    position_y_minus(current_figure);
  }
}

void position_x_minus(figure *current_figure) {
  for (int i = 0; i < 4; i++) {
    current_figure->position.x[i] -= 1;
  }
  current_figure->position.init_x -= 1;
}
void eq_old_x_new_x(figure *current_figure) {
  for (int i = 0; i < 4; i++) {
    current_figure->position.old_x[i] = current_figure->position.x[i];
  }
  current_figure->position.init_old_x = current_figure->position.init_x;
}

void position_x_plus(figure *current_figure) {
  for (int i = 0; i < 4; i++) {
    current_figure->position.x[i] += 1;
  }
  current_figure->position.init_x += 1;
}

void position_y_plus(figure *current_figure) {
  for (int i = 0; i < 4; i++) {
    current_figure->position.y[i] += 1;
  }
  current_figure->position.init_y += 1;
}
void position_y_minus(figure *current_figure) {
  for (int i = 0; i < 4; i++) {
    current_figure->position.y[i] -= 1;
  }
  current_figure->position.init_y -= 1;
}

void eq_old_y_new_y(figure *current_figure) {
  for (int i = 0; i < 4; i++) {
    current_figure->position.old_y[i] = current_figure->position.y[i];
  }
  current_figure->position.init_old_y = current_figure->position.init_y;
}
void  add_tmp_game_field(int (*tmp_game_field)[10],figure * tmp_current_figure, const int (*pieces)[4][4][4]){
   int k = -1;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
        if(pieces[tmp_current_figure->piece][tmp_current_figure->rotation][i][j] == 1){
      tmp_game_field[tmp_current_figure->position.init_y + i][tmp_current_figure->position.init_x + j] = pieces[tmp_current_figure->piece][tmp_current_figure->rotation][i][j];
          ++k;
          tmp_current_figure->position.old_y[k] = tmp_current_figure->position.init_y + i;
          tmp_current_figure->position.old_x[k] = tmp_current_figure->position.init_x + j;
          tmp_current_figure->position.y[k] = tmp_current_figure->position.init_y  + i;
          tmp_current_figure->position.x[k] = tmp_current_figure->position.init_x  + j;

        }
 

  
  }

  }
}
