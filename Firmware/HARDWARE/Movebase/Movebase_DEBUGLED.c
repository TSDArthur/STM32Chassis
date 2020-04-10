#include <sys.h>
#include <Movebase_DEBUGLED.h>

u8 Movebase_DEBUGLED_State = 0;

void Movebase_DEBUGLED_Init()
{
    GPIO_PinMode(GPIOF, RCC_AHB1Periph_GPIOF, GPIO_Pin_9 | GPIO_Pin_10,
                 GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
    return;
}

void Movebase_DEBUGLED_Set(u8 value)
{
    if (!value)
    {
        GPIO_WriteBit(GPIOF, GPIO_Pin_9, Bit_SET);
        GPIO_WriteBit(GPIOF, GPIO_Pin_10, Bit_SET);
    }
    else
    {
        GPIO_WriteBit(GPIOF, GPIO_Pin_9, Bit_RESET);
        GPIO_WriteBit(GPIOF, GPIO_Pin_10, Bit_RESET);
    }
    return;
}

void Movebase_DEBUGLED_Rotate()
{
    if (!Movebase_DEBUGLED_State)
    {
        GPIO_WriteBit(GPIOF, GPIO_Pin_9, Bit_SET);
        GPIO_WriteBit(GPIOF, GPIO_Pin_10, Bit_SET);
        Movebase_DEBUGLED_State = 1;
    }
    else
    {
        GPIO_WriteBit(GPIOF, GPIO_Pin_9, Bit_RESET);
        GPIO_WriteBit(GPIOF, GPIO_Pin_10, Bit_RESET);
        Movebase_DEBUGLED_State = 0;
    }
    return;
}
