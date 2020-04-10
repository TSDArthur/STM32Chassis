#ifndef __MOVEBASE_CONTROL_H
#define __MOVEBASE_CONTROL_H
#include <sys.h>
#include <IOManager.h>
#include <Movebase_MOTOR.h>
#include <Movebase_ENCODER.h>
#include <Movebase_KINEMATIC.h>
#include <Remote_RADIO.h>
#define MOVEBASE_CONTROL_DEBUG 0
#define MOVEBASE_CONTROL_K_SPEED (2700 * Movebase_CONTROL_ControlInv / 18840)
#define MOVEBASE_CONTROL_PULSE_TO_RAD (60000 / (Movebase_CONTROL_ControlInv * 2700))
extern int Movebase_CONTROL_MotorA_Speed;
extern int Movebase_CONTROL_MotorB_Speed;
extern int Movebase_CONTROL_MotorC_Speed;
extern int Movebase_CONTROL_MotorD_Speed;
extern int Movebase_CONTROL_MotorA_Speed_DEBUG;
extern int Movebase_CONTROL_MotorB_Speed_DEBUG;
extern int Movebase_CONTROL_MotorC_Speed_DEBUG;
extern int Movebase_CONTROL_MotorD_Speed_DEBUG;
extern int Movebase_CONTROL_ControlInv;
extern float Movebase_CONTROL_PID_KP;
extern float Movebase_CONTROL_PID_KI;
void Movebase_CONTROL_TimerInit(int ms);
void TIM6_DAC_IRQHandler(void);
void Movebase_CONTROL_SetSpeed(int Vx, int Vy, int Rw);
void Movebase_CONTROL_SetSpeedDebug(int motorA, int motorB, int motorC, int motor);
void Movebase_CONTROL_DoEventsDebug(void);
void Movebase_CONTROL_DoEvents(void);
void Movebase_CONTROL_SetPI(float KP, float KI);
int Movebase_CONTROL_PID_A(int currentSpeed, int targetSpeed);
int Movebase_CONTROL_PID_B(int currentSpeed, int targetSpeed);
int Movebase_CONTROL_PID_C(int currentSpeed, int targetSpeed);
int Movebase_CONTROL_PID_D(int currentSpeed, int targetSpeed);
#endif
