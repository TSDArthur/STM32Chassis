#include <sys.h>
#include <Remote_CONTROL.h>
u8 lastHookRotate = 0;
int controlValue[10] = {0};
float controlValueFloat[10] = {0};

int main(void)
{
    delay_init(168);
    Remote_CONTROL_Init();
    while (1)
    {
        //Remote_CONTROL_DoEvents();
        if (Remote_RADIO_FullRecieved('(', ')'))
        {
            int st = 1, pos = 0;
            for (int i = 1; i < Remote_RADIO_packSize; i++)
            {
                if (Remote_RADIO_radioRecieved[i] == ' ' || Remote_RADIO_radioRecieved[i] == ')')
                {
                    if (pos < 8)
                    {
                        controlValue[pos++] = Str2Int(Remote_RADIO_radioRecieved, st, i - 1);
                    }
                    else
                    {
                        controlValueFloat[pos++] = Str2Float(Remote_RADIO_radioRecieved, st, i - 1);
                    }
                    st = i + 1;
                }
            }
            Remote_RADIO_HasReaded();
            if (pos < 10)
            {
                continue;
            }
            Movebase_CONTROL_SetSpeed(controlValue[0], controlValue[1], controlValue[2]);
            Pulley_STEPPER_SetHeight(controlValue[3]);
            Pulley_VEHICLE_Run(PULLEY_VEHICLE_A, controlValue[4]);
            Pulley_VEHICLE_Run(PULLEY_VEHICLE_B, controlValue[5]);
            Pulley_VEHICLE_Run(PULLEY_VEHICLE_C, controlValue[6]);
            if (controlValue[7] && !lastHookRotate)
            {
                Pulley_VEHICLE_C_HookRotate();
                lastHookRotate = 1;
            }
            else if (!controlValue[7])
            {
                lastHookRotate = 0;
            }
            Movebase_CONTROL_SetPI(controlValueFloat[8], controlValueFloat[9]);
        }
    }
}
