#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/delay.h>
#include "DIO_interface.h"
#include"LCD_Interface.h"
#include "LCD_Cfg.h"
#include "LCD_Private.h"






void LCD_VidLCDInit()
{
  DIO_VidSetPortDirection(Data_Port, 255);
  DIO_VidSetPinDirection(Control_Port, rs_pin, High);
  DIO_VidSetPinDirection(Control_Port, rw_pin, High);
  DIO_VidSetPinDirection(Control_Port, en_pin, High);

  _delay_ms(35);
  LCD_VidSendCommand(FUN_SET);
  _delay_ms(1);
  LCD_VidSendCommand(DISP_ON_OFF);
  _delay_ms(1);
  LCD_VidSendCommand(LCD_CLEAR);
  _delay_ms(2);
}

void LCD_VidSendData (u8 Data)
{
  DIO_VidSetPinValue(Control_Port, rs_pin, High);
  DIO_VidSetPinValue(Control_Port, rw_pin, Low);
  DIO_VidSetPortValue(Data_Port, Data);
  DIO_VidSetPinValue(Control_Port, en_pin, High);
  _delay_ms(1);
  DIO_VidSetPinValue(Control_Port, en_pin, Low);
  _delay_ms(2);

}
void LCD_VidSendCommand (u8 command)
{
  DIO_VidSetPinValue(Control_Port, rs_pin, Low);
  DIO_VidSetPinValue(Control_Port, rw_pin, Low);
  DIO_VidSetPortValue(Data_Port, command);
  DIO_VidSetPinValue(Control_Port, en_pin, High);
  _delay_ms(1);
  DIO_VidSetPinValue(Control_Port, en_pin, Low);
  _delay_ms(2);

}
u8 LCD_VidSendString (u8 *Copy_U8String)
{
	u8 i;
  for (i = 0; Copy_U8String[i] !='\0'; i++)
  {
    LCD_VidSendData(Copy_U8String[i]);
  }
  return i;

}
void LCD_VidSendnum (s32 Copy_U32Num)
{
  u32 Local_reminder = 0;
  u32 Local_reverse = 0;
  u32 Local_temp;
  s32 Local_FlagCheck = Copy_U32Num;
  u8 negative_check = 0;
  u8 flag=0;

  /*Check for negative*/
  if(Copy_U32Num < 0)
  {
	  Copy_U32Num *= -1;
	  negative_check = 1;
  }

  /*Check for Zeros*/
  while(Local_FlagCheck%10 == 0)
  {
	  flag++;
	  Local_FlagCheck /=10;
  }

  /*Negative Print*/
  if(negative_check == 1)
  {
	  LCD_VidSendData('-');
  }

  /*Reverse Number*/
  while (Copy_U32Num !=0)
  {
	  Local_reminder = Copy_U32Num%10;
	  Local_reverse = Local_reverse*10 + Local_reminder;
	  Copy_U32Num /=10;
  }

/*Print Number*/
  while (Local_reverse != 0)

  {
    Local_temp = Local_reverse%10;
    LCD_VidSendData(Local_temp +'0');
    Local_reverse /= 10;
  }


  /*Print Zeros*/
  for(u8 i = 0; i<flag; i++)
  {
	LCD_VidSendData('0');
  }

}

void LCD_VidCursorPosition(u8 Copy_U8X_Position, u8 Copy_U8Y_Position)
{
	//LCD_VidSendCommand(LCD_CLEAR);
	u8 Local_Adress;
	if (Copy_U8X_Position== 0)
	{
		Local_Adress = 0X80;
	}
	else if(Copy_U8X_Position== 1)
	{
		Local_Adress = 0XC0;
	}
	if (Copy_U8Y_Position < 16)
	{
		Local_Adress += Copy_U8Y_Position;
	}
	LCD_VidSendCommand(Local_Adress);
}
void LCD_SendSpecialChar(u8* Copy_U8Patterns, u8 Copy_CharNumber)
{
	LCD_VidSendCommand(64+Copy_CharNumber*8);
	for(u8 i =0; i<8; i++)
	{
		LCD_VidSendData(Copy_U8Patterns[i]);
	}

}

void LCD_Clear(void)
{
  LCD_VidSendCommand(LCD_CLEAR);
}
