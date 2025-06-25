#include "key.h"
#include "delay.h"

void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // …œ¿≠ ‰»Î
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;  // PC8, PC9
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

u8 KEY_Scan(void)
{
    if (KEY_LEFT == 0)
    {
        delay_ms(10);
        if (KEY_LEFT == 0) return KEY_LEFT_PRES;
    }
    if (KEY_RIGHT == 0)
    {
        delay_ms(10);
        if (KEY_RIGHT == 0) return KEY_RIGHT_PRES;
    }
    return KEY_NONE;
}
