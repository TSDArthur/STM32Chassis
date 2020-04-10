#ifndef __MOVEBASE_ENCODER_H
#define __MOVEBASE_ENCODER_H
#include <sys.h>
#include <IOManager.h>
#define ENCODER_TIM_PERIOD (u16)(65535)
void Movebase_ENCODER_Init(void);
int Movebase_ENCODER_GetData(u8 Encoder);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);
#endif
