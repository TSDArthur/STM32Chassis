#include <sys.h>
#include <Pulley_STEPPER.h>

int Pulley_STEPPER_TargetHeight = 0;
int Pulley_STEPPER_CurrentHeight = 0;

void Pulley_STEPPER_Init()
{
    GPIO_PinMode(PULLEY_STEPPER_IOGROUP, PULLEY_STEPPER_IOGROUPCLK,
                 PULLEY_STEPPER_STEPPIN | PULLEY_STEPPER_DIRPIN, GPIO_Mode_OUT,
                 GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
    GPIO_WriteBit(GPIOC, PULLEY_STEPPER_DIRPIN, Bit_SET);
    GPIO_WriteBit(GPIOC, PULLEY_STEPPER_STEPPIN, Bit_RESET);
    Pulley_STEPPER_TimerInit();
    return;
}

void Pulley_STEPPER_TimerInit()
{
    int stepInv = 1000 / PULLEY_STEPPER_SPEED;
    stepInv /= 2;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = stepInv * 10 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 8400 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM7, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
}

void TIM7_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM7, TIM_IT_Update))
    {
        if (Pulley_STEPPER_CurrentHeight != Pulley_STEPPER_TargetHeight)
        {
            GPIO_WriteBit(PULLEY_STEPPER_IOGROUP, PULLEY_STEPPER_DIRPIN, Pulley_STEPPER_CurrentHeight > Pulley_STEPPER_TargetHeight ? Bit_RESET : Bit_SET);
            u8 stepIO = GPIO_ReadOutputDataBit(PULLEY_STEPPER_IOGROUP, PULLEY_STEPPER_STEPPIN);
            if (stepIO)
            {
                if (Pulley_STEPPER_CurrentHeight < Pulley_STEPPER_TargetHeight)
                {
                    Pulley_STEPPER_CurrentHeight++;
                }
                else
                {
                    Pulley_STEPPER_CurrentHeight--;
                }
            }
            GPIO_WriteBit(PULLEY_STEPPER_IOGROUP, PULLEY_STEPPER_STEPPIN, stepIO ? Bit_RESET : Bit_SET);
        }
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
    }
    return;
}

//Height : mm
void Pulley_STEPPER_SetHeight(float height)
{
    static float lastHeight = 0;
    if (lastHeight == height)
    {
        return;
    }
    float perRoundPulse = 360 / PULLEY_STEPPER_STEPANGLE;
    Pulley_STEPPER_TargetHeight = (int)(height / PULLEY_STEPPER_SCREWDIV) * perRoundPulse;
    lastHeight = height;
    return;
}

int Pulley_STEPPER_GetCurrentHeight()
{
    int retValue = 0;
    float perRoundPulse = 360 / PULLEY_STEPPER_STEPANGLE;
    float height = (Pulley_STEPPER_CurrentHeight / perRoundPulse) * PULLEY_STEPPER_SCREWDIV;
    retValue = (int)height;
    return retValue;
}
