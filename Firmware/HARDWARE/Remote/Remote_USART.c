#include <sys.h>
#include <string.h>
#include <stdlib.h>
#include <Remote_USART.h>

u8 RX1_BUFFER[RX1_BUFFER_LENGTH];
uint16_t RX1_BUFFER_FRONT = 0;
uint16_t RX1_BUFFER_TAIL = 0;
uint16_t RX1_BUFFER_SIZE = 0;
u8 RX2_BUFFER[RX2_BUFFER_LENGTH];
uint16_t RX2_BUFFER_FRONT = 0;
uint16_t RX2_BUFFER_TAIL = 0;
uint16_t RX2_BUFFER_SIZE = 0;
u8 RX3_BUFFER[RX3_BUFFER_LENGTH];
uint16_t RX3_BUFFER_FRONT = 0;
uint16_t RX3_BUFFER_TAIL = 0;
uint16_t RX3_BUFFER_SIZE = 0;

void Remote_USART1_Init(int BAUD)
{
    USART_Cmd(USART1, DISABLE);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    USART_InitTypeDef USART_InitStruc1;
    NVIC_InitTypeDef NVIC_InitStructure;
    memset(RX1_BUFFER, 0, sizeof(RX1_BUFFER));
    RX1_BUFFER_SIZE = 0;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    GPIO_PinMode(GPIOA, RCC_AHB1Periph_GPIOA, GPIO_Pin_9 | GPIO_Pin_10,
                 GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    USART_InitStruc1.USART_BaudRate = BAUD;
    USART_InitStruc1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruc1.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruc1.USART_Parity = USART_Parity_No;
    USART_InitStruc1.USART_StopBits = USART_StopBits_1;
    USART_InitStruc1.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruc1);
    USART_Cmd(USART1, ENABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_ClearFlag(USART1, USART_FLAG_TC);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);
    return;
}

void Remote_USART1_Send(const char *data)
{
    u8 bufferFlag;
    int length = strlen(data);
    int pos = 0;
    while (length)
    {
        bufferFlag = 1;
        if (!data[pos])
        {
            break;
        }
        while (bufferFlag)
        {
            bufferFlag = USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET;
        }
        USART_SendData(USART1, data[pos]);
        pos++;
        length--;
    }
    return;
}

void USART1_IRQHandler(void)
{
    u8 data;
    if (USART_GetITStatus(USART1, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
        data = USART_ReceiveData(USART1);
        RX1_BUFFER[RX1_BUFFER_TAIL] = data;
        RX1_BUFFER_TAIL = (RX1_BUFFER_TAIL + 1) % RX1_BUFFER_LENGTH;
        RX1_BUFFER_SIZE = (RX1_BUFFER_SIZE + 1) > RX1_BUFFER_LENGTH ? RX1_BUFFER_LENGTH : (RX1_BUFFER_SIZE + 1);
    }
    if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) == SET)
    {
        USART_ClearFlag(USART1, USART_FLAG_ORE);
        USART_ReceiveData(USART1);
    }
}

u8 Remote_USART1_Avaialable(void)
{
    return RX1_BUFFER_SIZE > 0;
}

char Remote_USART1_ReadByte(void)
{
    char data = '\0';
    if (RX1_BUFFER_SIZE)
    {
        data = RX1_BUFFER[RX1_BUFFER_FRONT];
        RX1_BUFFER_FRONT = (RX1_BUFFER_FRONT + 1) % RX1_BUFFER_LENGTH;
        RX1_BUFFER_SIZE = (RX1_BUFFER_SIZE - 1) < 0 ? 0 : (RX1_BUFFER_SIZE - 1);
    }
    return data;
}

void Remote_USART1_SendInt(int data)
{
    int level = 1;
    int tmp;
    int cnt = 0;
    u8 negative = data < 0;
    if (!data)
    {
        Remote_USART_Write(1, '0');
        return;
    }
    if (negative)
    {
        Remote_USART_Write(1, '-');
        data *= -1;
    }
    tmp = data;
    while (tmp)
    {
        tmp /= 10;
        level *= 10;
        cnt++;
    }
    level /= 10;
    for (int i = 0; i < cnt; i++)
    {
        char ch = (char)((int)(data / level) + '0');
        data %= level;
        level /= 10;
        Remote_USART_Write(1, ch);
    }
    return;
}

void Remote_USART1_SendFloat(float data)
{
    int data1;
    int data2;
    data1 = (int)data;
    if (data < 0)
    {
        data *= -1;
    }
    data2 = (int)(data * (float)100.0) % 100;
    Remote_USART1_SendInt(data1);
    Remote_USART1_Send(".");
    Remote_USART1_SendInt(data2);
    return;
}

void Remote_USART2_Init(int BAUD)
{
    USART_Cmd(USART2, DISABLE);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    USART_InitTypeDef USART_InitStruc1;
    NVIC_InitTypeDef NVIC_InitStructure;
    memset(RX2_BUFFER, 0, sizeof(RX2_BUFFER));
    RX2_BUFFER_SIZE = 0;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    GPIO_PinMode(GPIOA, RCC_AHB1Periph_GPIOA, GPIO_Pin_2 | GPIO_Pin_3,
                 GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
    USART_InitStruc1.USART_BaudRate = BAUD;
    USART_InitStruc1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruc1.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruc1.USART_Parity = USART_Parity_No;
    USART_InitStruc1.USART_StopBits = USART_StopBits_1;
    USART_InitStruc1.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART2, &USART_InitStruc1);
    USART_Cmd(USART2, ENABLE);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_ClearFlag(USART2, USART_FLAG_TC);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    return;
}

void Remote_USART2_Send(const char *data)
{
    u8 bufferFlag;
    int length = strlen(data);
    int pos = 0;
    while (length)
    {
        bufferFlag = 1;
        if (!data[pos])
        {
            break;
        }
        while (bufferFlag)
        {
            bufferFlag = USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET;
        }
        USART_SendData(USART2, data[pos]);
        pos++;
        length--;
    }
    return;
}

void USART2_IRQHandler(void)
{
    u8 data;
    if (USART_GetITStatus(USART2, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        data = USART_ReceiveData(USART2);
        RX2_BUFFER[RX2_BUFFER_TAIL] = data;
        RX2_BUFFER_TAIL = (RX2_BUFFER_TAIL + 1) % RX2_BUFFER_LENGTH;
        RX2_BUFFER_SIZE = (RX2_BUFFER_SIZE + 1) > RX2_BUFFER_LENGTH ? RX2_BUFFER_LENGTH : (RX2_BUFFER_SIZE + 1);
    }
    if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) == SET)
    {
        USART_ClearFlag(USART2, USART_FLAG_ORE);
        USART_ReceiveData(USART2);
    }
}

u8 Remote_USART2_Avaialable(void)
{
    return RX2_BUFFER_SIZE > 0;
}

char Remote_USART2_ReadByte(void)
{
    char data = '\0';
    if (RX2_BUFFER_SIZE)
    {
        data = RX2_BUFFER[RX2_BUFFER_FRONT];
        RX2_BUFFER_FRONT = (RX2_BUFFER_FRONT + 1) % RX2_BUFFER_LENGTH;
        RX2_BUFFER_SIZE = (RX2_BUFFER_SIZE - 1) < 0 ? 0 : (RX2_BUFFER_SIZE - 1);
    }
    return data;
}

void Remote_USART2_SendInt(int data)
{
    int level = 1;
    int tmp;
    int cnt = 0;
    u8 negative = data < 0;
    if (!data)
    {
        Remote_USART_Write(2, '0');
        return;
    }
    if (negative)
    {
        Remote_USART_Write(2, '-');
        data *= -1;
    }
    tmp = data;
    while (tmp)
    {
        tmp /= 10;
        level *= 10;
        cnt++;
    }
    level /= 10;
    for (int i = 0; i < cnt; i++)
    {
        char ch = (char)((int)(data / level) + '0');
        data %= level;
        level /= 10;
        Remote_USART_Write(2, ch);
    }
    return;
}

void Remote_USART2_SendFloat(float data)
{
    int data1;
    int data2;
    data1 = (int)data;
    if (data < 0)
    {
        data *= -1;
    }
    data2 = (int)(data * (float)100.0) % 100;
    Remote_USART2_SendInt(data1);
    Remote_USART2_Send(".");
    Remote_USART2_SendInt(data2);
    return;
}

void Remote_USART3_Init(int BAUD)
{
    USART_Cmd(USART3, DISABLE);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    USART_InitTypeDef USART_InitStruc1;
    NVIC_InitTypeDef NVIC_InitStructure;
    memset(RX3_BUFFER, 0, sizeof(RX3_BUFFER));
    RX3_BUFFER_SIZE = 0;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    GPIO_PinMode(GPIOB, RCC_AHB1Periph_GPIOB, GPIO_Pin_10 | GPIO_Pin_11,
                 GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
    USART_InitStruc1.USART_BaudRate = BAUD;
    USART_InitStruc1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruc1.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruc1.USART_Parity = USART_Parity_No;
    USART_InitStruc1.USART_StopBits = USART_StopBits_1;
    USART_InitStruc1.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART3, &USART_InitStruc1);
    USART_Cmd(USART3, ENABLE);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_ClearFlag(USART3, USART_FLAG_TC);
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    return;
}

void Remote_USART3_Send(const char *data)
{
    u8 bufferFlag;
    int length = strlen(data);
    int pos = 0;
    while (length)
    {
        bufferFlag = 1;
        if (!data[pos])
        {
            break;
        }
        while (bufferFlag)
        {
            bufferFlag = USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET;
        }
        USART_SendData(USART3, data[pos]);
        pos++;
        length--;
    }
    return;
}

void Remote_USART3_SendInt(int data)
{
    int level = 1;
    int tmp;
    int cnt = 0;
    u8 negative = data < 0;
    if (!data)
    {
        Remote_USART_Write(3, '0');
        return;
    }
    if (negative)
    {
        Remote_USART_Write(3, '-');
        data *= -1;
    }
    tmp = data;
    while (tmp)
    {
        tmp /= 10;
        level *= 10;
        cnt++;
    }
    level /= 10;
    for (int i = 0; i < cnt; i++)
    {
        char ch = (char)((int)(data / level) + '0');
        data %= level;
        level /= 10;
        Remote_USART_Write(3, ch);
    }
    return;
}

void Remote_USART3_SendFloat(float data)
{
    int data1;
    int data2;
    data1 = (int)data;
    if (data < 0)
    {
        data *= -1;
    }
    data2 = (int)(data * (float)100.0) % 100;
    Remote_USART3_SendInt(data1);
    Remote_USART3_Send(".");
    Remote_USART3_SendInt(data2);
    return;
}

void USART3_IRQHandler(void)
{
    u8 data;
    if (USART_GetITStatus(USART3, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
        data = USART_ReceiveData(USART3);
        RX3_BUFFER[RX3_BUFFER_TAIL] = data;
        RX3_BUFFER_TAIL = (RX3_BUFFER_TAIL + 1) % RX3_BUFFER_LENGTH;
        RX3_BUFFER_SIZE = (RX3_BUFFER_SIZE + 1) > RX3_BUFFER_LENGTH ? RX3_BUFFER_LENGTH : (RX3_BUFFER_SIZE + 1);
    }
    if (USART_GetFlagStatus(USART3, USART_FLAG_ORE) == SET)
    {
        USART_ClearFlag(USART3, USART_FLAG_ORE);
        USART_ReceiveData(USART3);
    }
}

u8 Remote_USART3_Avaialable(void)
{
    return RX3_BUFFER_SIZE > 0;
}

char Remote_USART3_ReadByte(void)
{
    char data = '\0';
    if (RX3_BUFFER_SIZE)
    {
        data = RX3_BUFFER[RX3_BUFFER_FRONT];
        RX3_BUFFER_FRONT = (RX3_BUFFER_FRONT + 1) % RX3_BUFFER_LENGTH;
        RX3_BUFFER_SIZE = (RX3_BUFFER_SIZE - 1) < 0 ? 0 : (RX3_BUFFER_SIZE - 1);
    }
    return data;
}

void Remote_USART_Init(u8 USARTx, int BAUD)
{
    switch (USARTx)
    {
    case 1:
        Remote_USART1_Init(BAUD);
        break;
    case 2:
        Remote_USART2_Init(BAUD);
        break;
    case 3:
        Remote_USART3_Init(BAUD);
        break;
    }
    return;
}

void Remote_USART_Write(u8 USARTx, char ch)
{
    char charBuff[2];
    charBuff[0] = ch;
    charBuff[1] = '\0';
    switch (USARTx)
    {
    case 1:
        Remote_USART1_Send(charBuff);
        break;
    case 2:
        Remote_USART2_Send(charBuff);
        break;
    case 3:
        Remote_USART3_Send(charBuff);
        break;
    }
    return;
}

void Remote_USART_Send(u8 USARTx, const char *str)
{
    switch (USARTx)
    {
    case 1:
        Remote_USART1_Send(str);
        break;
    case 2:
        Remote_USART2_Send(str);
        break;
    case 3:
        Remote_USART3_Send(str);
        break;
    }
    return;
}

void Remote_USART_SendInt(u8 USARTx, int data)
{
    switch (USARTx)
    {
    case 1:
        Remote_USART1_SendInt(data);
        break;
    case 2:
        Remote_USART2_SendInt(data);
        break;
    case 3:
        Remote_USART3_SendInt(data);
        break;
    }
    return;
}

void Remote_USART_SendFloat(u8 USARTx, float data)
{
    switch (USARTx)
    {
    case 1:
        Remote_USART1_SendFloat(data);
        break;
    case 2:
        Remote_USART2_SendFloat(data);
        break;
    case 3:
        Remote_USART3_SendFloat(data);
        break;
    }
    return;
}

u8 Remote_USART_Avaialable(u8 USARTx)
{
    u8 retValue = 0;
    switch (USARTx)
    {
    case 1:
        retValue = Remote_USART1_Avaialable();
        break;
    case 2:
        retValue = Remote_USART2_Avaialable();
        break;
    case 3:
        retValue = Remote_USART3_Avaialable();
        break;
    }
    return retValue;
}

char Remote_USART_ReadByte(u8 USARTx)
{
    char retValue = '\0';
    switch (USARTx)
    {
    case 1:
        retValue = Remote_USART1_ReadByte();
        break;
    case 2:
        retValue = Remote_USART2_ReadByte();
        break;
    case 3:
        retValue = Remote_USART3_ReadByte();
        break;
    }
    return retValue;
}
