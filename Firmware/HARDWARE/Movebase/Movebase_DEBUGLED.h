#ifndef __MOVEBASE_DEBUGLED_H
#define __MOVEBASE_DEBUGLED_H
#include <sys.h>
#include <IOManager.h>
extern u8 Movebase_DEBUGLED_State;
void Movebase_DEBUGLED_Init(void);
void Movebase_DEBUGLED_Set(u8 value);
void Movebase_DEBUGLED_Rotate(void);
#endif
