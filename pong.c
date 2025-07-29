#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25

#define MAX_SCORE 5

#define BALL_UP -1
#define BALL_DOWN 1
#define BALL_LEFT -2
#define BALL_RIGHT 2

#define LEFT_ROCKET_UP 'a'
#define LEFT_ROCKET_DOWN 'z'
#define RIGHT_ROCKET_UP 'k'
#define RIGHT_ROCKET_DOWN 'm'

bool is_left_collision(int ball_x, int ball_y, int left_rocket_y) {
  return ball_x <= 0 &&
         (left_rocket_y - 1 <= ball_y && ball_y <= left_rocket_y + 1);
}

bool is_right_collision(int ball_x, int ball_y, int right_rocket_y) {
  return ball_x >= FIELD_WIDTH - 1 &&
         (right_rocket_y - 1 <= ball_y && ball_y <= right_rocket_y + 1);
}

bool is_top_collision(int ball_y) { return ball_y <= 0; }

bool is_bottom_collision(int ball_y) { return ball_y >= FIELD_HEIGHT - 1; }

bool is_goal_to_left(int ball_x, int ball_y, int left_rocket_y,
                     int right_rocket_y) {
  return ball_x < 0 &&
         !(left_rocket_y - 1 <= ball_y && ball_y <= left_rocket_y + 1);
}

bool is_goal_to_right(int ball_x, int ball_y, int left_rocket_y,
                      int right_rocket_y) {
  return ball_x > FIELD_WIDTH - 1 &&
         !(right_rocket_y - 1 <= ball_y && ball_y <= right_rocket_y + 1);
}

void print_field(int ball_x, int ball_y, int left_rocket_y,
                 int right_rocket_y) {
  system("clear");

  for (int y = 0; y < FIELD_HEIGHT + 2; ++y) {
    for (int x = 0; x < FIELD_WIDTH + 2; ++x) {
      if (x == ball_x + 1 && y == ball_y + 1)
        printf("*");
      else if (x == 0 && (left_rocket_y <= y && y <= left_rocket_y + 2))
        printf("]");
      else if (x == FIELD_WIDTH + 1 &&
               (right_rocket_y <= y && y <= right_rocket_y + 2))
        printf("[");
      else if (y == 0 || y == FIELD_HEIGHT + 1)
        printf("=");
      else if (x == 0 || x == FIELD_WIDTH + 1)
        printf(".");
      else
        printf(" ");
    }
    printf("\n");
  }
}

char get_input() {
  char a;
  scanf("%c", &a);
  return a;
}

int main(void) {
  for (int A = 0, B = 0; A < MAX_SCORE && B < MAX_SCORE;) {
    int ball_x = 40, ball_y = 13;
    int left_rocket_y = 13, right_rocket_y = 13;
    print_field(ball_x, ball_y, left_rocket_y, right_rocket_y);

    int ball_x_direction = BALL_LEFT;
    int ball_y_direction = BALL_UP;

    while (true) {
      if (is_goal_to_left(ball_x, ball_y, left_rocket_y, right_rocket_y)) {
        ++B;
        break;
      } else if (is_goal_to_right(ball_x, ball_y, left_rocket_y,
                                  right_rocket_y)) {
        ++A;
        break;
      }

      char input = get_input();

      if (input == LEFT_ROCKET_UP) {
        if (left_rocket_y > 1)
          left_rocket_y--;
      } else if (input == LEFT_ROCKET_DOWN) {
        if (left_rocket_y < FIELD_HEIGHT - 2)
          left_rocket_y++;
      } else if (input == RIGHT_ROCKET_UP) {
        if (right_rocket_y > 1)
          right_rocket_y--;
      } else if (input == RIGHT_ROCKET_DOWN) {
        if (right_rocket_y < FIELD_HEIGHT - 2)
          right_rocket_y++;
      }

      ball_x += ball_x_direction;
      ball_y += ball_y_direction;

      if (is_top_collision(ball_y)) {
        ball_y = 0;
        ball_y_direction = BALL_DOWN;
      } else if (is_bottom_collision(ball_y)) {
        ball_y = FIELD_HEIGHT - 1;
        ball_y_direction = BALL_UP;
      }

      if (is_left_collision(ball_x, ball_y, left_rocket_y)) {
        ball_x = 0;
        ball_x_direction = BALL_RIGHT;
      } else if (is_right_collision(ball_x, ball_y, right_rocket_y)) {
        ball_x = FIELD_WIDTH - 1;
        ball_x_direction = BALL_LEFT;
      }

      print_field(ball_x, ball_y, left_rocket_y, right_rocket_y);
      printf("Left player score:\t%d\n", A);
      printf("Right player score:\t%d\n", B);
      printf("Max score:\t%d\n", MAX_SCORE);
    }
  }
}
