#include "lcd.h"
#include "snake.h"
#include <stdlib.h>

#define SNAKE_COLOR GREEN
#define FOOD_COLOR  RED
#define BG_COLOR    WHITE

extern Snake snake;

void draw_block(int x, int y, unsigned short color)
{
    LCD_Fill(x, y, x + BLOCK_SIZE - 1, y + BLOCK_SIZE - 1, color);
}

void draw_snake(Snake *snake)
{
    int i;
    for (i = 0; i < snake->length; i++) {
        draw_block(snake->body[i].x, snake->body[i].y, SNAKE_COLOR);
    }
}

void draw_food(Food *food)
{
    draw_block(food->pos.x, food->pos.y, FOOD_COLOR);
}

void snake_init(Snake *snake)
{
    int i;
    snake->length = 3;
    snake->direction = 1;
    for (i = 0; i < snake->length; i++) {
        snake->body[i].x = 40 - i * BLOCK_SIZE;
        snake->body[i].y = 40;
        draw_block(snake->body[i].x, snake->body[i].y, SNAKE_COLOR);
    }
}

int check_eat(Snake *snake, Food *food)
{
    return (snake->body[0].x == food->pos.x && snake->body[0].y == food->pos.y);
}

int check_die(Snake *snake)
{
    int i;
    Point head = snake->body[0];

    if (head.x < 0 || head.y < 0 || head.x >= WIDTH || head.y >= HEIGHT)
        return 1;

    for (i = 1; i < snake->length; i++) {
        if (head.x == snake->body[i].x && head.y == snake->body[i].y)
            return 1;
    }

    return 0;
}

void snake_move(Snake *snake, Food *food)
{
    int i;
    Point old_tail = snake->body[snake->length - 1];
    Point new_head = snake->body[0];
    int ate;

    switch (snake->direction) {
        case 0: new_head.y -= BLOCK_SIZE; break;
        case 1: new_head.x += BLOCK_SIZE; break;
        case 2: new_head.y += BLOCK_SIZE; break;
        case 3: new_head.x -= BLOCK_SIZE; break;
    }

    ate = (new_head.x == food->pos.x && new_head.y == food->pos.y);

    for (i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }

    snake->body[0] = new_head;
    draw_block(new_head.x, new_head.y, SNAKE_COLOR);

    if (!ate) {
        draw_block(old_tail.x, old_tail.y, BG_COLOR);  // 清除尾巴
    } else {
        snake->body[snake->length] = old_tail;         // 尾巴加入身体
        draw_block(old_tail.x, old_tail.y, SNAKE_COLOR);
        snake->length++;
        food->alive = 0;
    }
}

int is_point_on_snake(Snake *snake, int x, int y)
{
    int i;
    for (i = 0; i < snake->length; i++) {
        if (snake->body[i].x == x && snake->body[i].y == y)
            return 1;
    }
    return 0;
}

void food_create(Food *food)
{
    int x, y;

    while (1)
    {
        x = (rand() % (WIDTH / BLOCK_SIZE)) * BLOCK_SIZE;
        y = (rand() % (HEIGHT / BLOCK_SIZE)) * BLOCK_SIZE;

        if (!is_point_on_snake(&snake, x, y))
            break;
    }

    food->pos.x = x;
    food->pos.y = y;
    food->alive = 1;
}
