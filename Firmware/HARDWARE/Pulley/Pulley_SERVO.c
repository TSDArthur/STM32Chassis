#include <sys.h>
#include <Pulley_SERVO.h>

char Pulley_SERVO_Start = 0xff;
char Pulley_SERVO_Config = 0x02;
u8 Pulley_SERVO_USARTx = 0;
u8 Pulley_SERVO_Angle = 90;

void Pulley_SERVO_Init(u8 USARTx)
{
    Pulley_SERVO_USARTx = USARTx;
    Remote_USART_Init(Pulley_SERVO_USARTx, 9600);
}

void Pulley_SERVO_Write(u8 Channel, u8 Angle)
{
    Pulley_SERVO_Angle = Angle;
    short servoPulse = (short)(Angle * 11.11 + 500);
    servoPulse = servoPulse < 500 ? 500 : (servoPulse > 2500 ? 2500 : servoPulse);
    Remote_USART_Write(Pulley_SERVO_USARTx, Pulley_SERVO_Start);
    Remote_USART_Write(Pulley_SERVO_USARTx, Pulley_SERVO_Config);
    Remote_USART_Write(Pulley_SERVO_USARTx, Channel);
    Remote_USART_Write(Pulley_SERVO_USARTx, servoPulse & 0xff);
    Remote_USART_Write(Pulley_SERVO_USARTx, servoPulse >> 8);
    return;
}
