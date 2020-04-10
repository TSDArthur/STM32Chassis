#ifndef __IOManager_H
#define __IOManager_H
#include <sys.h>
void GPIO_PinMode(GPIO_TypeDef *GPIOx, uint32_t CLOCK, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, GPIOOType_TypeDef GPIO_OType, GPIOSpeed_TypeDef GPIO_Speed, GPIOPuPd_TypeDef GPIO_PuPd);
#endif
