#include "delay.h"
#include "sys.h"
#include "led.h"
#include "lcd.h"
#include "lcd_init.h"
#include "key.h"
#include "snake.h"

Snake snake;
Food food;

void update_direction(Snake *snake, u8 key)
{
    if (key == KEY_LEFT_PRES)
        snake->direction = (snake->direction + 3) % 4;
    else if (key == KEY_RIGHT_PRES)
        snake->direction = (snake->direction + 1) % 4;
}

int main(void)
{
    u8 key_val = 0;
    u8 key_lock = 0;
    u16 frame_count = 0;
    u16 speed_divider = 8;  // ?80ms????

    delay_init();
    LED_Init();
    LCD_Init();
    KEY_Init();

    LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);

    snake_init(&snake);
    food_create(&food);
    draw_food(&food);

    while (1)
    {
        key_val = KEY_Scan();

        if (key_val != KEY_NONE && key_lock == 0)
        {
            update_direction(&snake, key_val);
            key_lock = 1;
        }
        if (key_val == KEY_NONE)
        {
            key_lock = 0;
        }

        if (frame_count % speed_divider == 0)
        {
            snake_move(&snake, &food);

            if (check_eat(&snake, &food)) {
                food_create(&food);
                draw_food(&food);
            }

            if (check_die(&snake)) {
                LCD_ShowString(30, 60, "GAME OVER", RED, WHITE, 16, 0);
                break;
            }
        }

        LCD_ShowIntNum(0, 0, key_val, 1, RED, WHITE, 16);
        LCD_ShowIntNum(60, 0, snake.direction, 1, BLUE, WHITE, 16);

        frame_count++;
        delay_ms(10);
    }

    while (1);
}
