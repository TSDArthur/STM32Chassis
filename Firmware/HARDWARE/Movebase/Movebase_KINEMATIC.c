#include <Movebase_KINEMATIC.h>

long int Movebase_KINEMATIC_MotorA_Value = 0;
long int Movebase_KINEMATIC_MotorB_Value = 0;
long int Movebase_KINEMATIC_MotorC_Value = 0;
long int Movebase_KINEMATIC_MotorD_Value = 0;

float Movebase_KINEMATIC_Vx = 0;
float Movebase_KINEMATIC_Vy = 0;
float Movebase_KINEMATIC_Rw = 0;

float Movebase_KINEMATIC_Length_A = 0;
float Movebase_KINEMATIC_Length_B = 0;

/*
MotorB-MotorA
MotorC-MotorD
*/

void Movebase_KINEMATIC_SetVechicleSize(float a, float b)
{
    Movebase_KINEMATIC_Length_A = a;
    Movebase_KINEMATIC_Length_B = b;
    return;
}

void Movebase_KINEMATIC_SetTargetSpeed(float Vx, float Vy, float Rw)
{
    Movebase_KINEMATIC_Vx = Vx;
    Movebase_KINEMATIC_Vy = Vy;
    Movebase_KINEMATIC_Rw = Rw;
    Movebase_KINEMATIC_CalcMotorSpeed();
}

void Movebase_KINEMATIC_CalcMotorSpeed()
{
    float paraRw = (Movebase_KINEMATIC_Length_A + Movebase_KINEMATIC_Length_B) * Movebase_KINEMATIC_Rw;
    Movebase_KINEMATIC_MotorA_Value = Movebase_KINEMATIC_Vy + Movebase_KINEMATIC_Vx + paraRw;
    Movebase_KINEMATIC_MotorB_Value = Movebase_KINEMATIC_Vy - Movebase_KINEMATIC_Vx + paraRw;
    Movebase_KINEMATIC_MotorC_Value = -Movebase_KINEMATIC_Vy - Movebase_KINEMATIC_Vx + paraRw;
    Movebase_KINEMATIC_MotorD_Value = -Movebase_KINEMATIC_Vy + Movebase_KINEMATIC_Vx + paraRw;
    return;
}
