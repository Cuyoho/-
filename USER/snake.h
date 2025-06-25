#ifndef __SNAKE_H
#define __SNAKE_H

#define MAX_LENGTH 100
#define BLOCK_SIZE 8
#define WIDTH 128
#define HEIGHT 128

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point body[MAX_LENGTH];
    int length;
    int direction;
} Snake;

typedef struct {
    Point pos;
    int alive;
} Food;

void draw_block(int x, int y, unsigned short color);
void draw_snake(Snake *snake);
void draw_food(Food *food);
void snake_init(Snake *snake);
void snake_move(Snake *snake, Food *food);
int check_eat(Snake *snake, Food *food);
int check_die(Snake *snake);
void food_create(Food *food);
int is_point_on_snake(Snake *snake, int x, int y);

#endif
