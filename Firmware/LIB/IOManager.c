#include <sys.h>
#include <IOManager.h>

void GPIO_PinMode(GPIO_TypeDef *GPIOx, uint32_t CLOCK, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, GPIOOType_TypeDef GPIO_OType, GPIOSpeed_TypeDef GPIO_Speed, GPIOPuPd_TypeDef GPIO_PuPd)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(CLOCK, ENABLE);      //使能GPIOB时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;     //对应IO口
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode;   //输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType; //输出类型
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed; //输出速度
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd;   //上拉类型
    GPIO_Init(GPIOx, &GPIO_InitStructure);      //初始化GPIO
    GPIO_ResetBits(GPIOx, GPIO_Pin);
    return;
}
