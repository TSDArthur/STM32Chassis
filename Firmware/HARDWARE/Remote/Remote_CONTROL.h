#ifndef __REMOTE_CONTROL_H
#define __REMOTE_CONTROL_H
#include <sys.h>
#include <IOManager.h>
#include <STDFunctions.h>
#include <Remote_USART.h>
#include <Remote_RADIO.h>
#include <Movebase_MOTOR.h>
#include <Movebase_DEBUGLED.h>
#include <Movebase_KINEMATIC.h>
#include <Movebase_CONTROL.h>
#include <Pulley_SERVO.h>
#include <Pulley_STEPPER.h>
#include <Pulley_VEHICLE.h>
#define PULLEY_VEHICLE_SERVO_USART 3
#define REMOTE_RADIO_USART 2
#define REMOTE_CONTROL_VALUE_SIZE 8
#define REMOTE_CONTROL_MOVEBASE_SPEEDX 0
#define REMOTE_CONTROL_MOVEBASE_SPEEDY 1
#define REMOTE_CONTROL_MOVEBASE_SPEEDRW 2
#define REMOTE_CONTROL_STEPPER_HEIGHT 3
#define REMOTE_CONTROL_VEHICLE_A_STATE 4
#define REMOTE_CONTROL_VEHICLE_B_STATE 5
#define REMOTE_CONTROL_VEHICLE_C_STATE 6
#define REMOTE_CONTROL_VEHICLE_C_HOOK_ROTATE 7
extern int Remote_CONTROL_ControlValue[REMOTE_CONTROL_VALUE_SIZE];
void Remote_CONTROL_Init(void);
void Remote_CONTROL_DoEvents(void);
void Remote_CONTROL_Reporter_Init(int ms);
void TIM1_BRK_TIM9_IRQHandler(void);
#endif
