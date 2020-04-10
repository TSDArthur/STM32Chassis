#include <sys.h>
#include <Movebase_MOTOR.h>

//CH1-PA8 CH2-PE11 CH3-PE13 CH4-PA11
void Movebase_MOTOR_PWM_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE, ENABLE);
    GPIO_PinMode(GPIOA, RCC_AHB1Periph_GPIOA,
                 GPIO_Pin_8 | GPIO_Pin_11, GPIO_Mode_AF,
                 GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
    GPIO_PinMode(GPIOE, RCC_AHB1Periph_GPIOE,
                 GPIO_Pin_11 | GPIO_Pin_13, GPIO_Mode_AF,
                 GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_TIM1);
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void Movebase_MOTOR_Init(void)
{
    GPIO_PinMode(GPIOC, RCC_AHB1Periph_GPIOC,
                 AIN1 | AIN2 | BIN1 | BIN2 | CIN1 | CIN2 | DIN1 | DIN2,
                 GPIO_Mode_OUT, GPIO_OType_PP,
                 GPIO_Speed_100MHz, GPIO_PuPd_UP);
    Movebase_MOTOR_PWM_Init(8400, 1);
    Movebase_MOTOR_SetPWM(0, 0, 0, 0);
    return;
}

void Movebase_MOTOR_SetPWM(int16_t motor1Val, int16_t motor2Val, int16_t motor3Val, int16_t motor4Val)
{
    //Motor1
    if (motor1Val < 0)
    {
        motor1Val *= -1;
        GPIO_WriteBit(GPIOC, AIN1, Bit_RESET);
        GPIO_WriteBit(GPIOC, AIN2, Bit_SET);
    }
    else
    {
        GPIO_WriteBit(GPIOC, AIN1, Bit_SET);
        GPIO_WriteBit(GPIOC, AIN2, Bit_RESET);
    }
    //Motor2
    if (motor2Val < 0)
    {
        motor2Val *= -1;
        GPIO_WriteBit(GPIOC, BIN1, Bit_RESET);
        GPIO_WriteBit(GPIOC, BIN2, Bit_SET);
    }
    else
    {
        GPIO_WriteBit(GPIOC, BIN1, Bit_SET);
        GPIO_WriteBit(GPIOC, BIN2, Bit_RESET);
    }
    //Motor3
    if (motor3Val < 0)
    {
        motor3Val *= -1;
        GPIO_WriteBit(GPIOC, CIN1, Bit_RESET);
        GPIO_WriteBit(GPIOC, CIN2, Bit_SET);
    }
    else
    {
        GPIO_WriteBit(GPIOC, CIN1, Bit_SET);
        GPIO_WriteBit(GPIOC, CIN2, Bit_RESET);
    }
    //Motor4
    if (motor4Val < 0)
    {
        motor4Val *= -1;
        GPIO_WriteBit(GPIOC, DIN1, Bit_RESET);
        GPIO_WriteBit(GPIOC, DIN2, Bit_SET);
    }
    else
    {
        GPIO_WriteBit(GPIOC, DIN1, Bit_SET);
        GPIO_WriteBit(GPIOC, DIN2, Bit_RESET);
    }
    TIM1->CCR1 = motor1Val > MOVEBASE_MOTOR_MAXSPD ? MOVEBASE_MOTOR_MAXSPD : motor1Val;
    TIM1->CCR2 = motor2Val > MOVEBASE_MOTOR_MAXSPD ? MOVEBASE_MOTOR_MAXSPD : motor2Val;
    TIM1->CCR3 = motor3Val > MOVEBASE_MOTOR_MAXSPD ? MOVEBASE_MOTOR_MAXSPD : motor3Val;
    TIM1->CCR4 = motor4Val > MOVEBASE_MOTOR_MAXSPD ? MOVEBASE_MOTOR_MAXSPD : motor4Val;
}
