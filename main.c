/*
 * main.c
 *
 *  Created on: Nov 1, 2022
 *      Author: moham
 */
#include <avr/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "private.h"
#include"LCD_Interface.h"
#include "LCD_Cfg.h"
#include "DIO_interface.h"
#include "UART_Interface.h"
#include "UART_Cfg.h"
#include "funs.h"
#include "Timer1_Interface.h"
#include "Timer1_Cfg.h"
#include "ADC_Cfg.h"
#include "ADC_Interface.h"
#include "Timer_Interface.h"

int main(void)
{

	Funs_VidInit();
	Funs_VidLogIn();
	DIO_VidSetPinDirection(PORTD,PIN5,High);
	Funs_VidDoorOpen();

	while(1)
	{
		u8 read;
		LCD_Clear();
		LCD_VidSendString("Led: 0   Temp: 1");
		LCD_VidCursorPosition(1,0);
		LCD_VidSendString("Fan: 2   Door: 3");

		UART_VidSend(read);
		read = UART_U8Read();
		if(read == '0')
		{
			Funs_VidLedControl();
		}
		else if(read == '1')
		{
			Funs_VidTempControl();
		}
		else if(read == '2')
		{
			Funs_VidFanControl();
		}
		else if(read == '3')
		{
			Funs_VidDoorOpen();
		}
	}
}
