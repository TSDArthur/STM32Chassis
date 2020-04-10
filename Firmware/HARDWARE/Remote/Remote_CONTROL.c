#include <sys.h>
#include <Remote_CONTROL.h>

int Remote_CONTROL_ControlValue[REMOTE_CONTROL_VALUE_SIZE] = {0};

void Remote_CONTROL_Init()
{
    Remote_RADIO_Init(REMOTE_RADIO_USART);
    Remote_CONTROL_Reporter_Init(100);
    Pulley_STEPPER_Init();
    Pulley_SERVO_Init(PULLEY_VEHICLE_SERVO_USART);
    Pulley_VEHICLE_Init();
    Movebase_DEBUGLED_Init();
    Movebase_MOTOR_Init();
    Movebase_KINEMATIC_SetVechicleSize(0.421, 0.374);
    Movebase_ENCODER_Init();
    Movebase_CONTROL_SetPI(7, 4.5);
    Movebase_CONTROL_TimerInit(10);
    return;
}

void Remote_CONTROL_DoEvents()
{
    static uint8_t value[2];
    static u8 lastHookRotate = 0;
    if (Remote_RADIO_FullRecieved('(', ')'))
    {
        int st = 1, pos = 0;
        Remote_RADIO_Send(Remote_RADIO_radioRecieved);
        Remote_RADIO_Write('\n');
        for (int i = 1; i < Remote_RADIO_packSize; i++)
        {
            if (Remote_RADIO_radioRecieved[i] == ' ' || Remote_RADIO_radioRecieved[i] == ')')
            {
                value[pos++] = Str2Int(Remote_RADIO_radioRecieved, st, i - 1);
                st = i + 1;
            }
            if (pos == 2)
            {
                Remote_CONTROL_ControlValue[value[0]] = value[1];
                pos = 0;
            }
        }
        Remote_RADIO_HasReaded();
        Movebase_CONTROL_SetSpeed(Remote_CONTROL_ControlValue[REMOTE_CONTROL_MOVEBASE_SPEEDX],
                                  Remote_CONTROL_ControlValue[REMOTE_CONTROL_MOVEBASE_SPEEDY],
                                  Remote_CONTROL_ControlValue[REMOTE_CONTROL_MOVEBASE_SPEEDRW]);
        Pulley_STEPPER_SetHeight(Remote_CONTROL_ControlValue[REMOTE_CONTROL_STEPPER_HEIGHT]);
        Pulley_VEHICLE_Run(PULLEY_VEHICLE_A, Remote_CONTROL_ControlValue[REMOTE_CONTROL_VEHICLE_A_STATE]);
        Pulley_VEHICLE_Run(PULLEY_VEHICLE_B, Remote_CONTROL_ControlValue[REMOTE_CONTROL_VEHICLE_A_STATE]);
        Pulley_VEHICLE_Run(PULLEY_VEHICLE_C, Remote_CONTROL_ControlValue[REMOTE_CONTROL_VEHICLE_C_STATE]);
        if (Remote_CONTROL_ControlValue[REMOTE_CONTROL_VEHICLE_C_HOOK_ROTATE] && !lastHookRotate)
        {
            Pulley_VEHICLE_C_HookRotate();
            lastHookRotate = 1;
        }
        else if (!Remote_CONTROL_ControlValue[REMOTE_CONTROL_VEHICLE_C_HOOK_ROTATE])
        {
            lastHookRotate = 0;
        }
    }
    return;
}

void Remote_CONTROL_Reporter_Init(int ms)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = ms * 10 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 16800 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM9, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    return;
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM9, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
        Remote_RADIO_Send("(");
        Remote_RADIO_SendInt(Movebase_CONTROL_MotorA_Speed);
        Remote_RADIO_Send(" ");
        Remote_RADIO_SendInt(Movebase_CONTROL_MotorB_Speed);
        Remote_RADIO_Send(" ");
        Remote_RADIO_SendInt(Movebase_CONTROL_MotorC_Speed);
        Remote_RADIO_Send(" ");
        Remote_RADIO_SendInt(Movebase_CONTROL_MotorD_Speed);
        Remote_RADIO_Send(" ");
        Remote_RADIO_SendInt(Pulley_STEPPER_GetCurrentHeight());
        Remote_RADIO_Send(" ");
        Remote_RADIO_SendInt(Pulley_SERVO_Angle);
        Remote_RADIO_Send(" ");
        Remote_RADIO_SendFloat(Movebase_CONTROL_PID_KP);
        Remote_RADIO_Send(" ");
        Remote_RADIO_SendFloat(Movebase_CONTROL_PID_KI);
        Remote_RADIO_Send(")");
        Movebase_DEBUGLED_Rotate();
    }
    return;
}
