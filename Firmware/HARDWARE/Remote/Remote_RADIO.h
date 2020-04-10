#ifndef __REMOTE_RADIO_H
#define __REMOTE_RADIO_H
#include <sys.h>
#include <stdlib.h>
#include <string.h>
#include <delay.h>
#include <IOManager.h>
#include <Remote_USART.h>
#define RADIO_CONFIG_DATA_SIZE 7
#define RADIO_CONFIG_STATE_OK 4
#define RADIO_DATA_LENGTH 1024
extern const char radioConfig[RADIO_CONFIG_DATA_SIZE];
extern const char radioConfigOK[RADIO_CONFIG_STATE_OK];
extern char Remote_RADIO_radioRecieved[RADIO_DATA_LENGTH];
extern int Remote_RADIO_packSize;
extern uint8_t Remote_RADIO_USARTx;
void Remote_RADIO_Init(uint8_t USARTx);
void Remote_RADIO_Send(const char *str);
void Remote_RADIO_Write(char ch);
void Remote_RADIO_SendInt(int data);
void Remote_RADIO_SendFloat(float data);
u8 Remote_RADIO_FullRecieved(char symbolSt, char symbolEd);
void Remote_RADIO_HasReaded(void);
#endif
