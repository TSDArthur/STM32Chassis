#include <sys.h>
#include <Remote_RADIO.h>

char Remote_RADIO_radioRecieved[RADIO_DATA_LENGTH] = {0};
int Remote_RADIO_packSize = 0;
uint8_t Remote_RADIO_USARTx = 1;

void Remote_RADIO_Init(uint8_t USARTx)
{
    Remote_RADIO_USARTx = USARTx;
    Remote_USART_Init(Remote_RADIO_USARTx, 115200);
    memset(Remote_RADIO_radioRecieved, 0, sizeof(Remote_RADIO_radioRecieved));
    Remote_RADIO_packSize = 0;
    delay_ms(100);
    //MD0-PB12 MD1-PB13
    GPIO_PinMode(GPIOB, RCC_AHB1Periph_GPIOB,
                 GPIO_Pin_12 | GPIO_Pin_13, GPIO_Mode_OUT,
                 GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_UP);
    //AUX-PB14
    GPIO_PinMode(GPIOB, RCC_AHB1Periph_GPIOB,
                 GPIO_Pin_14, GPIO_Mode_IN,
                 GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_DOWN);
    //MD0->1 MD1->0
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);
    delay_ms(100);
    return;
}

void Remote_RADIO_Send(const char *str)
{
    Remote_USART_Send(Remote_RADIO_USARTx, str);
}

void Remote_RADIO_Write(char ch)
{
    Remote_USART_Write(Remote_RADIO_USARTx, ch);
}

void Remote_RADIO_SendInt(int data)
{
    Remote_USART_SendInt(Remote_RADIO_USARTx, data);
}

void Remote_RADIO_SendFloat(float data)
{
    Remote_USART_SendFloat(Remote_RADIO_USARTx, data);
}

u8 Remote_RADIO_FullRecieved(char symbolSt, char symbolEd)
{
    u8 retValue = 0;
    char ch;
    while (Remote_USART_Avaialable(Remote_RADIO_USARTx))
    {
        ch = Remote_USART_ReadByte(Remote_RADIO_USARTx);
        if (ch == '@' || ch == '\0')
        {
            continue;
        }
        if (ch == symbolSt)
        {
            Remote_RADIO_HasReaded();
        }
        Remote_RADIO_radioRecieved[Remote_RADIO_packSize++] = ch;
        if ((ch == symbolEd || Remote_RADIO_packSize == RADIO_DATA_LENGTH - 1) && Remote_RADIO_packSize > 1)
        {
            retValue = 1;
            Remote_RADIO_radioRecieved[Remote_RADIO_packSize] = '\0';
            break;
        }
    }
    return retValue;
}

void Remote_RADIO_HasReaded()
{
    Remote_RADIO_packSize = 0;
}
