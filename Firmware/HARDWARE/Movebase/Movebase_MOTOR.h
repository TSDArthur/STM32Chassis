#ifndef __MOVEBASE_MOTOR_H
#define __MOVEBASE_MOTOR_H
#include <sys.h>
#include <IOManager.h>
#define AIN1 GPIO_Pin_0
#define AIN2 GPIO_Pin_1
#define BIN1 GPIO_Pin_2
#define BIN2 GPIO_Pin_3
#define CIN1 GPIO_Pin_4
#define CIN2 GPIO_Pin_5
#define DIN1 GPIO_Pin_6
#define DIN2 GPIO_Pin_7
#define MOVEBASE_MOTOR_MAXSPD 8200
void Movebase_MOTOR_PWM_Init(u16 arr, u16 psc);
void Movebase_MOTOR_Init(void);
void Movebase_MOTOR_SetPWM(int16_t motor1Val, int16_t motor2Val, int16_t motor3Val, int16_t motor4Val);
#endif
