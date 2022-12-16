/*************************************************************************************************************************************************************************/
/*************************************************************************************************************************************************************************/
/*********************************************************    Auther: Mohamed Ehab      **********************************************************************************/
/*********************************************************    File: Interface of DIO    **********************************************************************************/
/*********************************************************    Date:3/9/2022             **********************************************************************************/
/*********************************************************    Version: 1                **********************************************************************************/
/*********************************************************    Desc:                     **********************************************************************************/
/*************************************************************************************************************************************************************************/
/*************************************************************************************************************************************************************************/




#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_VidLCDInit();
void LCD_VidSendData (u8 Data);
void LCD_VidSendCommand (u8 command);
u8 LCD_VidSendString (u8 *Copy_U8String);
void LCD_VidSendnum (s32 Copy_U32Num);
void LCD_VidCursorPosition(u8 Copy_U8X_Position, u8 Copy_U8Y_Position);
void LCD_SendSpecialChar(u8* Copy_U8Patterns, u8 Copy_CharNumber);
void LCD_Clear(void);





#endif






