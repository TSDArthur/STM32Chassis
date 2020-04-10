#include <sys.h>
#include <Movebase_CONTROL.h>

int Movebase_CONTROL_ControlInv = 10;
int Movebase_CONTROL_MotorA_Speed = 0;
int Movebase_CONTROL_MotorB_Speed = 0;
int Movebase_CONTROL_MotorC_Speed = 0;
int Movebase_CONTROL_MotorD_Speed = 0;
int Movebase_CONTROL_MotorA_Speed_DEBUG = 0;
int Movebase_CONTROL_MotorB_Speed_DEBUG = 0;
int Movebase_CONTROL_MotorC_Speed_DEBUG = 0;
int Movebase_CONTROL_MotorD_Speed_DEBUG = 0;
float Movebase_CONTROL_PID_KP = 10;
float Movebase_CONTROL_PID_KI = 2;

void Movebase_CONTROL_TimerInit(int ms)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    Movebase_CONTROL_ControlInv = ms;
    TIM_TimeBaseStructure.TIM_Period = Movebase_CONTROL_ControlInv * 10 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 8400 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM6, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
}

void TIM6_DAC_IRQHandler()
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) == SET)
    {
        if (MOVEBASE_CONTROL_DEBUG)
        {
            Movebase_CONTROL_DoEventsDebug();
        }
        else
        {
            Movebase_CONTROL_DoEvents();
        }
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    }
    return;
}

//CM/S
void Movebase_CONTROL_SetSpeed(int Vx, int Vy, int Rw)
{
    float pulseVx = Vx * MOVEBASE_CONTROL_K_SPEED;
    float pulseVy = Vy * MOVEBASE_CONTROL_K_SPEED;
    float pulseRw = Rw * 18.84 * MOVEBASE_CONTROL_K_SPEED;
    Movebase_KINEMATIC_SetTargetSpeed(pulseVx, pulseVy, pulseRw);
}

void Movebase_CONTROL_SetSpeedDebug(int motorA, int motorB, int motorC, int motorD)
{
    Movebase_CONTROL_MotorA_Speed_DEBUG = motorA;
    Movebase_CONTROL_MotorB_Speed_DEBUG = motorB;
    Movebase_CONTROL_MotorC_Speed_DEBUG = motorC;
    Movebase_CONTROL_MotorD_Speed_DEBUG = motorD;
    return;
}

void Movebase_CONTROL_DoEventsDebug()
{
    int EncoderA = Movebase_ENCODER_GetData(1);
    int EncoderB = Movebase_ENCODER_GetData(2);
    int EncoderC = Movebase_ENCODER_GetData(3);
    int EncoderD = Movebase_ENCODER_GetData(4);
    Movebase_CONTROL_MotorA_Speed = EncoderA * MOVEBASE_CONTROL_PULSE_TO_RAD;
    Movebase_CONTROL_MotorB_Speed = EncoderB * MOVEBASE_CONTROL_PULSE_TO_RAD;
    Movebase_CONTROL_MotorC_Speed = EncoderC * MOVEBASE_CONTROL_PULSE_TO_RAD;
    Movebase_CONTROL_MotorD_Speed = EncoderD * MOVEBASE_CONTROL_PULSE_TO_RAD;
    int MotorA = Movebase_CONTROL_PID_A(EncoderA, Movebase_CONTROL_MotorA_Speed_DEBUG / MOVEBASE_CONTROL_PULSE_TO_RAD);
    int MotorB = Movebase_CONTROL_PID_B(EncoderB, Movebase_CONTROL_MotorB_Speed_DEBUG / MOVEBASE_CONTROL_PULSE_TO_RAD);
    int MotorC = Movebase_CONTROL_PID_C(EncoderC, Movebase_CONTROL_MotorC_Speed_DEBUG / MOVEBASE_CONTROL_PULSE_TO_RAD);
    int MotorD = Movebase_CONTROL_PID_D(EncoderD, Movebase_CONTROL_MotorD_Speed_DEBUG / MOVEBASE_CONTROL_PULSE_TO_RAD);
    Movebase_MOTOR_SetPWM(MotorA, MotorB, MotorC, MotorD);
    return;
}

void Movebase_CONTROL_DoEvents()
{
    int EncoderA = Movebase_ENCODER_GetData(1);
    int EncoderB = Movebase_ENCODER_GetData(2);
    int EncoderC = Movebase_ENCODER_GetData(3);
    int EncoderD = Movebase_ENCODER_GetData(4);
    Movebase_CONTROL_MotorA_Speed = EncoderA * MOVEBASE_CONTROL_PULSE_TO_RAD;
    Movebase_CONTROL_MotorB_Speed = EncoderB * MOVEBASE_CONTROL_PULSE_TO_RAD;
    Movebase_CONTROL_MotorC_Speed = EncoderC * MOVEBASE_CONTROL_PULSE_TO_RAD;
    Movebase_CONTROL_MotorD_Speed = EncoderD * MOVEBASE_CONTROL_PULSE_TO_RAD;
    int MotorA = Movebase_CONTROL_PID_A(EncoderA, Movebase_KINEMATIC_MotorA_Value);
    int MotorB = Movebase_CONTROL_PID_B(EncoderB, Movebase_KINEMATIC_MotorB_Value);
    int MotorC = Movebase_CONTROL_PID_C(EncoderC, Movebase_KINEMATIC_MotorC_Value);
    int MotorD = Movebase_CONTROL_PID_D(EncoderD, Movebase_KINEMATIC_MotorD_Value);
    Movebase_MOTOR_SetPWM(MotorA, MotorB, MotorC, MotorD);
    return;
}

//CM/S
void Movebase_CONTROL_SetPI(float KP, float KI)
{
    Movebase_CONTROL_PID_KP = KP;
    Movebase_CONTROL_PID_KI = KI;
    return;
}

int Movebase_CONTROL_PID_A(int currentSpeed, int targetSpeed)
{
    static int error = 0, last_error = 0, pwm_output = 0;
    error = currentSpeed - targetSpeed;
    pwm_output += Movebase_CONTROL_PID_KP * (error - last_error) + Movebase_CONTROL_PID_KI * error;
    last_error = error;
    if (pwm_output > MOVEBASE_MOTOR_MAXSPD)
    {
        pwm_output = MOVEBASE_MOTOR_MAXSPD;
    }
    if (pwm_output < -1 * MOVEBASE_MOTOR_MAXSPD)
    {
        pwm_output = -1 * MOVEBASE_MOTOR_MAXSPD;
    }
    return pwm_output;
}

int Movebase_CONTROL_PID_B(int currentSpeed, int targetSpeed)
{
    static int error = 0, last_error = 0, pwm_output = 0;
    error = currentSpeed - targetSpeed;
    pwm_output += Movebase_CONTROL_PID_KP * (error - last_error) + Movebase_CONTROL_PID_KI * error;
    last_error = error;
    if (pwm_output > MOVEBASE_MOTOR_MAXSPD)
    {
        pwm_output = MOVEBASE_MOTOR_MAXSPD;
    }
    if (pwm_output < -1 * MOVEBASE_MOTOR_MAXSPD)
    {
        pwm_output = -1 * MOVEBASE_MOTOR_MAXSPD;
    }
    return pwm_output;
}

int Movebase_CONTROL_PID_C(int currentSpeed, int targetSpeed)
{
    static int error = 0, last_error = 0, pwm_output = 0;
    error = currentSpeed - targetSpeed;
    pwm_output += Movebase_CONTROL_PID_KP * (error - last_error) + Movebase_CONTROL_PID_KI * error;
    last_error = error;
    if (pwm_output > MOVEBASE_MOTOR_MAXSPD)
    {
        pwm_output = MOVEBASE_MOTOR_MAXSPD;
    }
    if (pwm_output < -1 * MOVEBASE_MOTOR_MAXSPD)
    {
        pwm_output = -1 * MOVEBASE_MOTOR_MAXSPD;
    }
    return pwm_output;
}

int Movebase_CONTROL_PID_D(int currentSpeed, int targetSpeed)
{
    static int error = 0, last_error = 0, pwm_output = 0;
    error = currentSpeed - targetSpeed;
    pwm_output += Movebase_CONTROL_PID_KP * (error - last_error) + Movebase_CONTROL_PID_KI * error;
    last_error = error;
    if (pwm_output > MOVEBASE_MOTOR_MAXSPD)
    {
        pwm_output = MOVEBASE_MOTOR_MAXSPD;
    }
    if (pwm_output < -1 * MOVEBASE_MOTOR_MAXSPD)
    {
        pwm_output = -1 * MOVEBASE_MOTOR_MAXSPD;
    }
    return pwm_output;
}
