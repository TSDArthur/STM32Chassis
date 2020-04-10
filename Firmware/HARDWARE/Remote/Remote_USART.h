#ifndef __REMOTE_USART_H
#define __REMOTE_USART_H
#include <sys.h>
#include <IOManager.h>
#define RX1_BUFFER_LENGTH 1024
#define RX2_BUFFER_LENGTH 1024
#define RX3_BUFFER_LENGTH 1024
extern u8 RX1_BUFFER[RX1_BUFFER_LENGTH];
extern uint16_t RX1_BUFFER_FRONT;
extern uint16_t RX1_BUFFER_TAIL;
extern uint16_t RX1_BUFFER_SIZE;
extern u8 RX2_BUFFER[RX1_BUFFER_LENGTH];
extern uint16_t RX2_BUFFER_FRONT;
extern uint16_t RX2_BUFFER_TAIL;
extern uint16_t RX2_BUFFER_SIZE;
extern u8 RX3_BUFFER[RX3_BUFFER_LENGTH];
extern uint16_t RX3_BUFFER_FRONT;
extern uint16_t RX3_BUFFER_TAIL;
extern uint16_t RX3_BUFFER_SIZE;
void Remote_USART1_Init(int BAUD);
void Remote_USART1_Send(const char *data);
void USART1_IRQHandler(void);
u8 Remote_USART1_Avaialable(void);
char Remote_USART1_ReadByte(void);
void Remote_USART1_SendInt(int data);
void Remote_USART1_SendFloat(float data);
void Remote_USART2_Init(int BAUD);
void Remote_USART2_Send(const char *data);
void USART2_IRQHandler(void);
u8 Remote_USART2_Avaialable(void);
char Remote_USART2_ReadByte(void);
void Remote_USART2_SendInt(int data);
void Remote_USART2_SendFloat(float data);
void Remote_USART3_Init(int BAUD);
void Remote_USART3_Send(const char *data);
void USART3_IRQHandler(void);
u8 Remote_USART3_Avaialable(void);
char Remote_USART3_ReadByte(void);
void Remote_USART3_SendInt(int data);
void Remote_USART3_SendFloat(float data);
void Remote_USART_Init(u8 USARTx, int BAUD);
void Remote_USART_Write(u8 USARTx, char ch);
void Remote_USART_Send(u8 USARTx, const char *str);
void Remote_USART_SendInt(u8 USARTx, int data);
void Remote_USART_SendFloat(u8 USARTx, float data);
u8 Remote_USART_Avaialable(u8 USARTx);
char Remote_USART_ReadByte(u8 USARTx);
#endif
