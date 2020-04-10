#ifndef __PULLEY_STEPPER_H
#define __PULLEY_STEPPER_H
#include <sys.h>
#include <IOManager.h>
#define PULLEY_STEPPER_SPEED 300
#define PULLEY_STEPPER_STEPANGLE 1.8
#define PULLEY_STEPPER_SCREWDIV 1
#define PULLEY_STEPPER_IOGROUP GPIOE
#define PULLEY_STEPPER_IOGROUPCLK RCC_AHB1Periph_GPIOE
#define PULLEY_STEPPER_STEPPIN GPIO_Pin_3
#define PULLEY_STEPPER_DIRPIN GPIO_Pin_2
extern int Pulley_STEPPER_TargetHeight;
extern int Pulley_STEPPER_CurrentHeight;
void Pulley_STEPPER_Init(void);
void Pulley_STEPPER_TimerInit(void);
void TIM7_IRQHandler(void);
void Pulley_STEPPER_SetHeight(float height);
int Pulley_STEPPER_GetCurrentHeight(void);
#endif

