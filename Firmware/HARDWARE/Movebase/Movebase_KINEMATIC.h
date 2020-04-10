#ifndef __MOVEBASE_KINEMATIC_H
#define __MOVEBASE_KINEMATIC_H
#include <sys.h>
#include <IOManager.h>
#include <Movebase_MOTOR.h>
extern long int Movebase_KINEMATIC_MotorA_Value;
extern long int Movebase_KINEMATIC_MotorB_Value;
extern long int Movebase_KINEMATIC_MotorC_Value;
extern long int Movebase_KINEMATIC_MotorD_Value;
extern float Movebase_KINEMATIC_Vx;
extern float Movebase_KINEMATIC_Vy;
extern float Movebase_KINEMATIC_Rw;
extern float Movebase_KINEMATIC_Length_A;
extern float Movebase_KINEMATIC_Length_B;
void Movebase_KINEMATIC_SetVechicleSize(float a, float b);
void Movebase_KINEMATIC_SetTargetSpeed(float Vx, float Vy, float Rw);
void Movebase_KINEMATIC_CalcMotorSpeed(void);
#endif
