#ifndef __PULLEY_SERVO_H
#define __PULLEY_SERVO_H
#include <sys.h>
#include <IOManager.h>
#include <Remote_USART.h>
extern char Pulley_SERVO_Start;
extern char Pulley_SERVO_Config;
extern u8 Pulley_SERVO_USARTx;
extern u8 Pulley_SERVO_Angle;
void Pulley_SERVO_Init(u8 USARTx);
void Pulley_SERVO_Write(u8 Channel, u8 Angle);
#endif
